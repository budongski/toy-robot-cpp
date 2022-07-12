#pragma once
namespace toyrobot
{
	struct LeftPayload
	{
		bool valid;
		inline static const char* id = "LEFT";
		static LeftPayload extract(const std::string& args)
		{
			return LeftPayload { args.empty() }; // valid if there is no param
		}
	};
}
