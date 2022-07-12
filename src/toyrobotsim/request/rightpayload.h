#pragma once
namespace toyrobot
{
	struct RightPayload
	{
		bool valid;
		inline static const char* id = "RIGHT";
		static RightPayload extract(const std::string& args)
		{
			return RightPayload { args.empty() }; // valid if there is no param
		}
	};
}
