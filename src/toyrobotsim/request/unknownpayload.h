#pragma once

namespace toyrobot
{
	struct UnknownPayload
	{
		std::string rawString;
		static UnknownPayload extract(const std::string& args)
		{
			return UnknownPayload { !args.empty() ? args : std::string("(empty)") };
		}
	};
}
