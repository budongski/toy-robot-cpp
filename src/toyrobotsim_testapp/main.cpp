#include "toyrobotsim.h"
#include "testsequence.h"
#include <iostream>

using namespace test;

void usage()
{
	std::cout << "\ntestapp.exe T --> Run in Test mode. Fixed commands with expected behavior.";
	std::cout << "\ntestapp.exe C --> Take commands from command line (5x5 board)";
	std::cout << "\ntestapp.exe X Y [source]" <<
		"\n\twhere" <<
		"\n\tX - number of rows" <<
		"\n\tY - number of columns" <<
		"\n\tsource - filename in current directory, or command line if empty" << std::endl;
}

bool readOptions(int argc, char* argv[], Options& options)
{
	try
	{
		if (argc == 2 && (argv[1][0] == 'C' || argv[1][0] == 'c'))
		{
			options = { 5, 5, Options::SourceType::console, "", true };
			std::cout << "\nWaiting for command.." << std::endl;
		}
		else if (argc == 2 && (argv[1][0] == 'T' || argv[1][0] == 't'))
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
		else
		{
			options.rows = argc > 1 ? std::stoi(argv[1]) : 5;
			options.cols = argc > 2 ? std::stoi(argv[2]) : 5;
			options.source = argc > 3 ? Options::file : Options::console;
			options.other = argc > 3 ? argv[3] : "";
			options.verbose = true;
		}
	}
	catch (...)
	{
		std::cout << "\nInvalid options.";
		return false;
	}

	return true;
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
		for (int i = 0; i < reports.size(); ++i)
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

	//bool result = std::equal(expectedResults.begin(), expectedResults.end(), reports.begin());
	return result;
}

int main(int argc, char* argv[])
{
	Options options;
	if ( (argc < 2) || !readOptions(argc, argv, options))
	{
		usage();
		return 0;
	}

	ToyRobotSim sim(options);
	std::vector<std::string> reports;
	auto result = sim.run(reports);


	if (options.source == Options::SourceType::mem)
	{
		if (verify(reports))
		{
			std::cout << "\n\nTEST SUCCESS" << std::endl;
		}
		else
		{ 
			std::cout << "\n\nTEST FAILED" << std::endl;
		}
		
	}

	return static_cast<int>(result);
}

