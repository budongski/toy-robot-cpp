#pragma once

#include "request/reportpayload.h"
#include <functional>

namespace toyrobot
{
	class Board;
	class ReportingAgent
		: public toyrobot::ReceiverWithPayload<ReportPayload>
	{
	public:
		using ReportCallback = std::function<void(const std::string& report)>;
		ReportingAgent(Board* board, ReportCallback mCallback);
		virtual ~ReportingAgent();

		virtual void execute(const ReportPayload& params) override;

	private:
		Board* mBoard;
		ReportCallback mCallback;
	};
}
