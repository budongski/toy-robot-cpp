#include "toyrobotsim.h"
#include "testsequence.h"
#include <iostream>

using namespace test;

void usage()
{
	std::cout << "\ntestapp.exe --> Take commands from command line (5x5 board)";
	std::cout << "\ntestapp.exe -t --> Run in Test mode. Fixed commands with expected behavior.";
	std::cout << "\ntestapp.exe [source] X Y" <<
		"\n\twhere" <<
		"\n\tsource - filename in current directory, or command line if empty" 
		"\n\tX - number of rows" <<
		"\n\tY - number of columns" << std::endl;

}

bool readOptions(int argc, char* argv[], Options& options)
{
	bool validArgs = true;
	try
	{
		if (argc == 1)
		{
			options = { 5, 5, Options::SourceType::console, "", true };
			std::cout << "\nWaiting for command.." << std::endl;
		}
		else if (argc == 2 && 
			(argv[1][0] == '-' || argv[1][0] == '/') &&
			(argv[1][1] == 'T' || argv[1][1] == 't'))
		{
			// create input source from testdata
			std::string source;
			for (const auto& str : gTestSequence5X5)
			{
				source.append(str.first);
			}
			options = { 5, 5, Options::SourceType::mem, source, true };
			std::cout << "\nRunning tests.." << std::endl;
		}
		else if (argc == 4)
		{
			options.other = argv[1];	// filename
			options.rows = std::stoi(argv[2]);
			options.cols = std::stoi(argv[3]);
			options.source = Options::SourceType::file;
			options.verbose = true;
		}
		else
		{
			validArgs = false;
		}
	}
	catch (...)
	{
		validArgs = false;
	}

	return validArgs;
}

bool verify(const std::vector<std::string>& reports)
{
	std::cout << "\n\nVERIFYING reports" << std::endl;
	bool result = true;
	std::vector<std::string> expectedResults;
	for (const auto& expected : gTestSequence5X5)
	{
		expectedResults.push_back(expected.second);
	}

	if (expectedResults.size() != reports.size())
	{
		std::cout << "\n\nTEST FAILED. Mismatch in number of results" << std::endl;
		result = false;
	}
	else
	{
		for (size_t i = 0; i < reports.size(); ++i)
		{
			if (expectedResults[i].compare(reports[i]) != 0)
			{

				std::cout << "\nMismatch in result of command line " << i << "."
					<< "\n\texpected: " << expectedResults[i]
					<< "\n\tactual: " << reports[i]
					<< std::endl;
				result = false;
			}
		}
	}

	std::cout << "\n\n" << (result ? "TEST SUCCESS" : "TEST FAILED") << std::endl;

	return result;
}

int main(int argc, char* argv[])
{
	Options options;
	if (!readOptions(argc, argv, options))
	{
		std::cout << "\nInvalid options.\n";
		usage();
		return 0;
	}

	ToyRobotSim sim(options);
	std::vector<std::string> reports;
	auto result = sim.run(reports);

	if (result == ResultCode::success)
	{
		if (options.source == Options::SourceType::mem)
		{
			verify(reports);
		}
	}
	else
	{
		std::cout << "Error code: " << static_cast<int>(result) << std::endl;
	}

	return 0;
}

