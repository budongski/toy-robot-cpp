#pragma once

#include <framework/commandsource.h>
#include <string>
#include <istream>
#include <optional>

namespace toyrobot
{
	class StreamReader : public toyrobot::Reader
	{
	public:
		StreamReader(std::istream& stream);
		virtual ~StreamReader() = default;
		virtual std::optional<std::string> getline() override;

	private:
		std::istream& mStream;
		bool mOpen;
	};
};
