#pragma once

namespace toyrobot
{
	class Receiver
	{
	public:
		virtual ~Receiver() {}
		virtual void execute() {};
	};


	template <typename Payload>
	class ReceiverWithPayload : public Receiver
	{
	public:
		virtual ~ReceiverWithPayload() {}
		virtual void execute(const Payload& params) = 0;
	};

	// using ReceiverPtr = Receiver * ;

	template <typename Payload>
	using ReceiverPtr = ReceiverWithPayload<Payload>* ;

}
