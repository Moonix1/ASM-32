#pragma once

#include <vector>

#include "Token.h"
#include "Lexer.h"
#include "Expr.h"

namespace ASM32 {

	class Parser {
	public:
		Parser(Lexer &lexer)
			: m_Lexer(lexer) {
			m_Token = m_Lexer.NextToken();
		}

		void Parse();
	public:
		const std::vector<std::shared_ptr<Expr>> &GetExprs() const { return m_Exprs; }
	private:
		void Eat(TokenType type);

		void ParseExpr();
		void ParseOpcode();
		void ParseDirective();
	private:
		Lexer &m_Lexer;
		Token m_Token;

		std::vector<std::shared_ptr<Expr>> m_Exprs;
	};

}