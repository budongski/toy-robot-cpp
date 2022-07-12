#include "simpletokenizer.h"
#include <algorithm>

namespace toyrobot
{
    SimpleTokenizer::SimpleTokenizer() 
        : mSep(" \t")
    {
    }

    toyrobot::CommandTokens SimpleTokenizer::tokenize(const std::string& line) 
    {
        toyrobot::CommandTokens tokens;

        // do a series of whitespace searches
        // to split the string into {keyword, parameters}
        // should be linear-fast. every next search begins on the last offset
        do
        {
            auto idStart = line.find_first_not_of(mSep);
            if (idStart == std::string::npos)
                break;

            auto idEnd = line.find_first_of(mSep, idStart);
            if (idEnd == std::string::npos)
            {
                tokens.id = line.substr(idStart);
                break;
            }

            tokens.id = line.substr(idStart, idEnd - idStart);

            auto paramsStart = line.find_first_not_of(mSep, idEnd);
            if (paramsStart == std::string::npos)
                break;

            auto paramsEnd = line.find_last_not_of(mSep);
            if (paramsEnd == line.size() - 1)
            {
                tokens.params = line.substr(paramsStart);
                break;
            }
            tokens.params = line.substr(paramsStart, paramsEnd - paramsStart + 1);
        } while (0);

        std::transform(tokens.id.begin(), tokens.id.end(), tokens.id.begin(), 
                   [](unsigned char c){ return std::toupper(c); });
        std::transform(tokens.params.begin(), tokens.params.end(), tokens.params.begin(), 
                   [](unsigned char c){ return std::toupper(c); });

        return tokens;
    }
}
