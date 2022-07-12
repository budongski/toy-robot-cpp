#pragma once
namespace toyrobot
{
	struct MovePayload
	{
		bool valid;
		inline static const char* id = "MOVE";
		static MovePayload extract(const std::string& args)
		{
			return MovePayload { args.empty() }; // valid if there is no param
		}
	};
}
