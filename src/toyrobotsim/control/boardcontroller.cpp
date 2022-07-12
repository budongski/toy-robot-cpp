#include "boardcontroller.h"

namespace toyrobot
{
	BoardController::BoardController(Board* board, LoggingCallback callback, bool verbose)
		: mBoard(board)
		, mCallback(callback)
		, mVerbose(verbose)
	{
	}

	BoardController::~BoardController() 
	{
	}

	void BoardController::execute(const PlacePayload& payload)
	{
		if (!payload.valid)
		{
			logCommandError();
			return;
		}

		auto err = mBoard->placeRobot(0, toyrobot::Transform4D{ payload.x, payload.y, payload.face });
		logBoardError(err);
	}

	void BoardController::execute(const MovePayload& payload)
	{
		if (!payload.valid)
		{
			logCommandError();
			return;
		}
		auto err = mBoard->forwardRobot(0);
		logBoardError(err);
	}

	void BoardController::execute(const LeftPayload& payload)
	{
		if (!payload.valid)
		{
			logCommandError();
			return;
		}
		auto err = mBoard->turnRobotLeft(0);
		logBoardError(err);
	}

	void BoardController::execute(const RightPayload& payload)
	{
		if (!payload.valid)
		{
			logCommandError();
			return;
		}
		auto err = mBoard->turnRobotRight(0);
		logBoardError(err);
	}

	void BoardController::execute(const UnknownPayload& params)
	{
		if (mVerbose)
		{
			auto msg = strutils::format("unknown_command: \"%s\"", params.rawString.c_str());
			mCallback(msg);
		}
	}

	void BoardController::logCommandError()
	{
		if (mVerbose)
		{
			mCallback("failed_to_parse_payload");
		}
	}

	void BoardController::logBoardError(BoardError err)
	{
		auto msg = Board::toString(err);
		if (mVerbose)
		{
			std::string report;
			mBoard->report(0, report);
			msg.append(":");
			msg.append(report);
		}
		if (mVerbose || err != BoardError::success)
		{
			mCallback(msg);
		}
	}
};