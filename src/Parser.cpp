#include "Parser.h"

#include "Log.h"

#include "Defines.h"

namespace ASM32 {

	void Parser::Parse() {
		while (m_Token.type != END_OF_FILE) {
			ParseExpr();
		}

		INFO("{0}", m_Exprs.size());
	}

	void Parser::Eat(TokenType type) {
		if (m_Token.type != type) {
			ERROR("parser: unexpected token: `{0}`, expected: `{1}`", TokenTypeToString(m_Token.type), TokenTypeToString(type));
			exit(1);
		}

		m_Token = m_Lexer.NextToken();
	}

	void Parser::ParseExpr() {
		switch (m_Token.type) {
		case SECTION:
			return ParseDirective();
		case MOV:
		case HLT:
			return ParseOpcode();
		default: {
			ERROR("parser: unexpected token `{0}`", TokenTypeToString(m_Token.type));
			exit(1);
		} break;
		}

		m_Token = m_Lexer.NextToken();
	}

	void Parser::ParseOpcode() {
		switch (m_Token.type) {
		case MOV: {
			Eat(TokenType::MOV);
			std::string reg = m_Token.value;
			Eat(TokenType::REG);

			Eat(TokenType::COMMA);

			u64 immediate = std::stoull(m_Token.value);
			Eat(TokenType::IMMEDIATE);

			m_Exprs.push_back(std::make_shared<MoveExpr>(
				std::make_shared<RegisterExpr>(reg),
				std::make_shared<NumberExpr>(immediate)
			));
		} break;
		case HLT: {
			Eat(TokenType::HLT);
			m_Exprs.push_back(std::make_shared<HaltExpr>());
		} break;
		}
	}

	void Parser::ParseDirective() {
		switch (m_Token.type) {
		case SECTION: {
			if (m_Token.value == "section") {
				Eat(SECTION);
			}

			m_Exprs.push_back(std::make_shared<SectionExpr>(m_Token.value));
			Eat(SECTION);
		} break;
		}
	}

}