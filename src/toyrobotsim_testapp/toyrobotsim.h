#pragma once
#include <framework/commandsource.h>
#include <framework/receiver.h>
#include <framework/registry.h>

#include "model/board.h"
#include "control/boardcontroller.h"
#include "control/reportingagent.h"

#include <sstream>
#include <fstream>

namespace test
{
	struct Options {
		enum class SourceType {
			console,
			file,
			mem
		};

		int rows;
		int cols;
		SourceType source;
		std::string other;
		bool verbose;
	};

	enum class ResultCode
	{
		success,
		board_setup_failure, 
		input_load_failure, 
		unknown_exception,
		test_assert_failure, // todo
	};

	class ToyRobotSim
	{

	public:
		ToyRobotSim(const Options& options);
		~ToyRobotSim() = default;

		ResultCode run(std::vector<std::string>& outputReports);

	private:
		std::unique_ptr<toyrobot::Reader> setupReader();
		Options mOptions;
		std::ifstream mSourceFile;
		std::istringstream mSourceSS;
	};
}

