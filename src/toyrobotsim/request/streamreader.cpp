#include "streamreader.h"

namespace toyrobot
{
	StreamReader::StreamReader(std::istream& stream)
		: mStream(stream)
	{
	}

	std::optional<std::string> StreamReader::getline()
	{
		if (!mStream.eof())
		{
			std::string line;
			std::getline(mStream, line);
			return line;
		}

		return std::nullopt;
	}
}
