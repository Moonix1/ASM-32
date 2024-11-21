#pragma once

#include <string>

namespace ASM32 {

	enum TokenType {
		// Others
		IDENT,

		// Operand types
		IMMEDIATE,
		REG,

		// Directives
		SECTION,

		// Opcodes
		MOV,
		HLT,

		// Special characters
		COLON,
		COMMA,

		// End of file
		END_OF_FILE,
	};

	inline std::string TokenTypeToString(TokenType type) {
		switch (type) {
		case IDENT:			return "IDENT"; break;
		case IMMEDIATE:		return "IMMEDIATE"; break;
		case REG:			return "REG"; break;
		case SECTION:		return "SECTION"; break;
		case MOV:			return "MOV"; break;
		case HLT:			return "HLT"; break;
		case COLON:			return "COLON"; break;
		case COMMA:			return "COMMA"; break;
		case END_OF_FILE:	return "EOF"; break;
		}
	}

	struct Token {
		TokenType type;
		std::string value;
	};

}