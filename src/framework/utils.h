#pragma once
#include <string>
#include <sstream>

namespace toyrobot
{
	namespace strutils
	{
		inline static std::string trim(const std::string& source, const std::string& sep)
		{
			std::string s(source);
			s.erase(0, s.find_first_not_of(sep));
			s.erase(s.find_last_not_of(sep) + 1);
			return s;
		}

		template <int N>
		inline static std::array<std::string, N> split(const std::string& source, const char sep)
		{
			std::stringstream ss(source);
			int index = 0;
			std::array<std::string, N> lines;
			while (std::getline(ss, lines[index], sep) && (++index < N)) {
			};

			return lines;
		}

		template<typename... Args>
		std::string format(const std::string& format, Args... args)
		{
			size_t size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
			std::unique_ptr<char[]> buf(new char[size]);
			std::snprintf(buf.get(), size, format.c_str(), args...);
			return std::string(buf.get(), buf.get() + size - 1);
		}
	}
}

