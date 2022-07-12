#pragma once

#include <framework/command.h>
#include <framework/receiver.h>

#include "placepayload.h"
#include "movepayload.h"
#include "leftpayload.h"
#include "rightpayload.h"
#include "reportpayload.h"
#include "unknownpayload.h"

namespace toyrobot
{
	class UnknownCommand : public toyrobot::CommandWithPayload<UnknownPayload>
	{
	public:

		UnknownCommand(toyrobot::ReceiverPtr<UnknownPayload> receiver, const std::string& args)
			: CommandWithPayload<UnknownPayload>(receiver, args)
		{
		}

		virtual ~UnknownCommand() = default;
		virtual void execute() override {
			mReceiver->execute(mPayload);
		}
	};

	class PlaceCommand : public toyrobot::CommandWithPayload<PlacePayload>
	{
	public:

		PlaceCommand(toyrobot::ReceiverPtr<PlacePayload> receiver, const std::string& args)
			: CommandWithPayload<PlacePayload>(receiver, args)
		{
		}

		virtual ~PlaceCommand() = default;
		virtual void execute() override {
			mReceiver->execute(mPayload);
		}
	};

	class MoveCommand : public toyrobot::CommandWithPayload<MovePayload>
	{
	public:
		MoveCommand(toyrobot::ReceiverPtr<MovePayload> receiver, const std::string& args)
			: CommandWithPayload<MovePayload>(receiver, args)
		{
		}

		virtual ~MoveCommand() = default;
		virtual void execute() override {
			mReceiver->execute(mPayload);
		}
	};

	class LeftCommand : public toyrobot::CommandWithPayload<LeftPayload>
	{
	public:
		LeftCommand(toyrobot::ReceiverPtr<LeftPayload> receiver, const std::string& args)
			: CommandWithPayload<LeftPayload>(receiver, args)
		{
		}

		virtual ~LeftCommand() = default;
		virtual void execute() override {
			mReceiver->execute(mPayload);
		}
	};

	class RightCommand : public toyrobot::CommandWithPayload<RightPayload>
	{
	public:

		RightCommand(toyrobot::ReceiverPtr<RightPayload> receiver, const std::string& args)
			: CommandWithPayload<RightPayload>(receiver, args)
		{
		}

		virtual ~RightCommand() = default;
		virtual void execute() override {
			mReceiver->execute(mPayload);
		}
	};

	class ReportCommand : public toyrobot::CommandWithPayload<ReportPayload>
	{
	public:

		ReportCommand(toyrobot::ReceiverPtr<ReportPayload> receiver, const std::string& args)
			: CommandWithPayload<ReportPayload>(receiver, args)
		{
		}

		virtual ~ReportCommand() = default;
		virtual void execute() override {
			mReceiver->execute(mPayload);
		}
	};
}
