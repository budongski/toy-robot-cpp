#include "toyrobotsim.h"

#include "request/boardcommands.h"
#include "request/streamreader.h"
#include "request/simpletokenizer.h"
#include <vector>
#include <iostream>

namespace test
{
	using namespace toyrobot;

	ToyRobotSim::ToyRobotSim(const Options& options)
		: mOptions(options)
	{
	}

	std::unique_ptr<toyrobot::Reader> ToyRobotSim::setupReader()
	{
		switch (mOptions.source)
		{
		case Options::file:
			mSourceFile.open(mOptions.other);
			if (mSourceFile.is_open())
				return std::make_unique<StreamReader>(mSourceFile);
			break;
		case Options::mem:
			mSourceSS.str(mOptions.other);
			if (mSourceSS.good())
				return std::make_unique<StreamReader>(mSourceSS);
			break;
		case Options::console:
		default:
			return std::make_unique<StreamReader>(std::cin);
			break;
		}
		return nullptr;
	}

	ResultCode ToyRobotSim::run(std::vector<std::string>& outputReports)
	{
		auto result = ResultCode::success;

		try
		{
			// initialize file, command line, or sstream reader
			auto reader = setupReader();
			if (!reader)
				return ResultCode::input_load_failure;

			toyrobot::CommandSource source;
			source.setReader(std::move(reader));
			source.setTokenizer(std::make_unique<SimpleTokenizer>());

			// setup domain object. 
			Board board(mOptions.rows, mOptions.cols);

			// Commands are not directly acting on the domain object
			// There is a middle man that is subscribed to the commands at compile time
			// - board controller for Robot movements
			// - I separated reporting agent for the Report command
			// to demo that a command can be applied to any object by binding it to some receiver
			BoardController boardController(&board, 
				[&](const std::string& errorMessage) {
					std::cout << errorMessage << std::endl; 
					outputReports.push_back(errorMessage);
				},
				mOptions.verbose // verbose (log successful moves)
				);

			// let's capture the reports by callback,
			// useful for testing end to end
			ReportingAgent reporter(&board, [&](const std::string& report) 
				{
					auto msg = strutils::format("report:%s", report.c_str());
					std::cout << msg << std::endl;
					outputReports.push_back(msg);
				});

			// bind command to receiver.
			// receiver should be subscribed to the payload at compile time
			// ie, if PlaceCommand<PlacePayload> is bound to boardController,
			// boardController must derive from Receiver<PlacePayload>
			// and implement an action for PlacePayload
			// if not, the error is caught at compile time
			toyrobot::Registry registry;
			auto ok =
				registry.addCreator(PlacePayload::id, [&](const std::string& args) {
				return std::make_unique<PlaceCommand>(&boardController, args); })

				&& registry.addCreator(MovePayload::id, [&](const std::string& args) {
				return std::make_unique<MoveCommand>(&boardController, args); })

				&& registry.addCreator(LeftPayload::id, [&](const std::string& args) {
				return std::make_unique<LeftCommand>(&boardController, args); })

				&& registry.addCreator(RightPayload::id, [&](const std::string& args) {
				return std::make_unique<RightCommand>(&boardController, args); })

				&& registry.addCreator(ReportPayload::id, [&](const std::string& args) {
				return std::make_unique<ReportCommand>(&reporter, args); })

				&& registry.addUnknownCreator([&](const std::string& args) {
				return std::make_unique<UnknownCommand>(&boardController, args); });

			if (!ok)
			{
				return ResultCode::board_setup_failure;
			}

			// loops through the source until end of file or ctrl+z
			while (1)
			{
				// produces the id and parameter strings
				auto tokens = source.next();

				// exits on end of stream, because commandsource returns nullopt
				if (tokens.has_value() == false)
					break;

				// command object with payload extracted from parameters
				if (auto cmd = registry.makeCommand(tokens.value().id, tokens.value().params);
					cmd != nullptr)
				{
					// there is no intermediate invoker,
					// relevant functionalities can be achieved in BoardController and Reporting Agent
					cmd->execute();
				}
			};
		}
		catch (...)
		{
			result = ResultCode::unknown_exception;
		}

		return result;
	}
}
