#pragma once
namespace toyrobot
{
	struct ReportPayload
	{
		bool valid;
		inline static const char* id = "REPORT";
		static ReportPayload extract(const std::string& args)
		{
			return ReportPayload { args.empty() }; // valid if there is no param
		}
	};
}
