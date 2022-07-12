#pragma once
#include "command.h"
#include <memory>
#include <optional>

namespace toyrobot
{
	class Reader
	{
	public:
		Reader() = default;
		virtual ~Reader() {}
		virtual std::optional<std::string> getline() = 0;
	};

	class Tokenizer 
	{
	public:
		Tokenizer() = default;
		virtual ~Tokenizer() {}
		virtual CommandTokens tokenize(const std::string& line) = 0;
	};

	class CommandSource
	{
	public:
		CommandSource()
			: mReader(nullptr)
			, mTokenizer(nullptr)
		{
		}

		CommandSource(std::unique_ptr<Reader> reader, std::unique_ptr<Tokenizer> translator)
			: mReader(std::move(reader))
			, mTokenizer(std::move(translator))
		{
		}

		void setReader(std::unique_ptr<Reader> reader)
		{
			mReader = std::move(reader);
		}

		void setTokenizer(std::unique_ptr<Tokenizer> tokenizer)
		{
			mTokenizer = std::move(tokenizer);
		}

		virtual ~CommandSource()
		{
		}

		std::optional<CommandTokens> next() 
		{
			// default order to read commands
			auto line = mReader->getline();
			if(line.has_value())
				return mTokenizer->tokenize(line.value());
			return std::nullopt;
		}

	private:
		std::unique_ptr<Reader> mReader;
		std::unique_ptr<Tokenizer> mTokenizer;
	};
}
