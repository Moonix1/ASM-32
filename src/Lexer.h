#pragma once

#include <string>

#include "Token.h"

namespace ASM32 {

	class Lexer {
	public:
		Lexer(std::string source)
			: m_Source(source), m_Pos(0), m_Char(source[0]) {}

		Token NextToken();
	private:
		void Advance();
		Token AdvanceWith(Token tok);

		Token LexWord();
		Token LexNumber();
	private:
		std::string m_Source;
		size_t m_Pos;
		char m_Char;
	};

}