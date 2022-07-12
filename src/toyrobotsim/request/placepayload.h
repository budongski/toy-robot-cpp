#pragma once

#include <framework/gridmath.h>
#include <framework/utils.h>
#include <regex>

namespace toyrobot
{
	template<typename MovePolicy>
	struct PlacePayloadGeneric
	{
		int x = 0;
		int y = 0;
		std::string face;
		bool valid = false;

		inline static const char* id = "PLACE";
		inline static const unsigned int argCount = 3;
		static PlacePayloadGeneric extract(const std::string& src)
		{
			static const std::regex re = std::regex("(\\d+)(\\s+)?,(\\s+)?(\\d+)(\\s+)?,(\\s+)?(\\w+)");
			PlacePayloadGeneric payload;
			payload.valid = std::regex_match(src, re);
			if (payload.valid)
			{
				const auto params = strutils::split<argCount>(src, ',');
				payload.x = std::stoi(params[0]);	// works even with whitespaces
				payload.y = std::stoi(params[1]);	// works even with whitespaces
				payload.face = strutils::trim(params[2], " \t");	// need to trim, then check against directions defined by MovePolicy
				if (MovePolicy::rotationToIndex(payload.face) == -1)
				{
					payload.valid = false;
				}
			}
			return payload;
		}
	};

	using PlacePayload = toyrobot::PlacePayloadGeneric<toyrobot::MovePolicy4Directions>;
};
