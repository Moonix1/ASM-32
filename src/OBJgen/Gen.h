#pragma once

#include <fstream>
#include <vector>
#include <memory>

#include "Expr.h"
#include "Headers.h"

namespace ASM32 {

	class OBJGen {
	public:
		OBJGen(std::vector<std::shared_ptr<Expr>> exprs, std::string outputName);
		~OBJGen();
	private:
		void GenerateProgram();

		void GenerateNumber64(u64 val);
	private:
		std::vector<std::shared_ptr<Expr>> m_Exprs;
		u32 m_Pos = 0;

		u32 m_VAddr = 0x400000;

		std::vector<Symbol> m_Symbols;

		std::ofstream m_File;
	};

}