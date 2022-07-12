#pragma once

#include <framework/commandsource.h>

namespace toyrobot
{
    class SimpleTokenizer : public toyrobot::Tokenizer
    {
    public:
        SimpleTokenizer();
        virtual ~SimpleTokenizer() = default;
        virtual toyrobot::CommandTokens tokenize(const std::string& line) override;

    private:
        const std::string mSep;
    };
};
