#include "Lexer.h"

#include "Log.h"

namespace ASM32 {
	
	Token Lexer::NextToken() {
		if (m_Pos < m_Source.size()) {
			while (isspace(m_Char)) { Advance(); }

			if (isalpha(m_Char) || m_Char == '_' || m_Char == '.') {
				return AdvanceWith(LexWord());
			}

			if (isdigit(m_Char)) {
				return AdvanceWith(LexNumber());
			}

			switch (m_Char) {
			case ':': {
				return AdvanceWith(Token {
					.type = COLON,
					.value = ":",
				});
			} break;
			case ',': {
				return AdvanceWith(Token {
					.type = COMMA,
					.value = ",",
					});
			} break;

			default: {
				ERROR("unexpected character: `{0}`", m_Char);
				exit(1);
			} break;
			}
		} else {
			return Token { .type = END_OF_FILE, .value = "\0" };
		}
	}

	void Lexer::Advance() {
		m_Pos += 1;
		m_Char = m_Source[m_Pos];
	}

	Token Lexer::AdvanceWith(Token tok) {
		Advance();
		return tok;
	}

	Token Lexer::LexWord() {
		size_t start = m_Pos;
		while (m_Pos < m_Source.size() && (isalnum(m_Char) || m_Char == '_' || m_Char == '.')) {
			Advance();
		}

		std::string value = m_Source.substr(start, m_Pos - start);
		m_Pos -= 1;

		if (value == "section") { return Token { .type = SECTION, .value = value }; }
		else if (value == ".text") { return Token { .type = SECTION, .value = value }; }
		else if (value == ".data") { return Token { .type = SECTION, .value = value }; }
		else if (value == "mov") { return Token { .type = MOV, .value = value }; }
		else if (value == "hlt") { return Token { .type = HLT, .value = value }; }
		else if (value == "mov") { return Token { .type = MOV, .value = value }; }
		else if (
				(value == "rax") || (value == "rsp") || (value == "r8")  || (value == "r12") ||
				(value == "rbx") || (value == "rbp") || (value == "r9")  || (value == "r13") ||
				(value == "rcx") || (value == "rsi") || (value == "r10") || (value == "r14") ||
				(value == "rdx") || (value == "rdi") || (value == "r11") || (value == "r15")
			) { return Token { .type = REG, .value = value }; }
		else {
			return Token { .type = IDENT, .value = value };
		}
	}

	Token Lexer::LexNumber() {
		size_t start = m_Pos;
		while (m_Pos < m_Source.size() && isalnum(m_Char)) {
			Advance();
		}

		std::string value = m_Source.substr(start, m_Pos - start);
		m_Pos -= 1;

		return Token { .type = IMMEDIATE, .value = value };
	}

}