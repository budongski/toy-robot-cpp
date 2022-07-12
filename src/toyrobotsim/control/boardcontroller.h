#pragma once

#include "request/placepayload.h"
#include "request/movepayload.h"
#include "request/leftpayload.h"
#include "request/rightpayload.h"
#include "request/unknownpayload.h"
#include "model/board.h"
#include <functional>

namespace toyrobot
{
	class BoardController
		: public toyrobot::ReceiverWithPayload<LeftPayload>
		, public toyrobot::ReceiverWithPayload<RightPayload>
		, public toyrobot::ReceiverWithPayload<MovePayload>
		, public toyrobot::ReceiverWithPayload<PlacePayload>
		, public toyrobot::ReceiverWithPayload<UnknownPayload>
	{
	public:
		using LoggingCallback = std::function<void(const std::string& report)>;
		BoardController(Board* board, LoggingCallback callback, bool verbose);
		virtual ~BoardController();

		virtual void execute(const PlacePayload& params) override;
		virtual void execute(const MovePayload& params) override;
		virtual void execute(const LeftPayload& params) override;
		virtual void execute(const RightPayload& params) override;
		virtual void execute(const UnknownPayload& params) override;

	private:
		Board* mBoard;
		LoggingCallback mCallback;
		const bool mVerbose;

		void logBoardError(BoardError err);
		void logCommandError();
	};
}
