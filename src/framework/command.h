#pragma once

#include <string>
#include <vector>
#include "receiver.h"

namespace toyrobot
{
	struct CommandTokens 
    {
		std::string id;
		std::string params;
	};

    class Command 
    {
    public:
        virtual ~Command() {}
        virtual void execute() = 0;
    };

	template <typename Payload>
	class CommandWithPayload : public toyrobot::Command
	{
	public:
		CommandWithPayload(toyrobot::ReceiverPtr<Payload> receiver, const std::string& args)
			: mReceiver(receiver)
			, mPayload(Payload::extract(args))
		{
		}
		virtual ~CommandWithPayload() {}

		virtual void execute() override = 0;

	protected:
		toyrobot::ReceiverPtr<Payload> mReceiver;
		Payload mPayload;
	};

    //using CommandPtr = Command*;

	template <typename Payload>
	using CommandPtr = CommandWithPayload<Payload>*;
}
