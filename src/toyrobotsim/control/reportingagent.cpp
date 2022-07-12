#include "model/board.h"
#include "reportingagent.h"
#include <iostream>

namespace toyrobot
{
	ReportingAgent::ReportingAgent(Board* board, ReportCallback callback)
		: mBoard(board)
		, mCallback(callback)
	{
	}

	ReportingAgent::~ReportingAgent()
	{
	}

	void ReportingAgent::execute(const ReportPayload& payload)
	{
		std::string report;
		if(mBoard->report(0, report) == BoardError::success)
			mCallback(report);
		else
			mCallback("Nothing to report");
	}
};