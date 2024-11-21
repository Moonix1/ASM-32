#pragma once

#include <memory>
#include <string>

#include "Defines.h"

namespace ASM32 {

	struct Expr {
		virtual ~Expr() = default;
	};

	struct NumberExpr : public Expr {
	public:
		NumberExpr(u64 value)
			: m_Value(value) {}
	public:
		u64 m_Value;
	};
	struct RegisterExpr : public Expr {
	public:
		RegisterExpr(std::string value)
			: m_Value(value) {}
	public:
		std::string m_Value;
	};

	struct SectionExpr : public Expr {
	public:
		SectionExpr(std::string sect)
			: m_Section(sect) {}
	public:
		std::string m_Section;
	};

	struct MoveExpr : public Expr {
	public:
		MoveExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs)
			: m_LHS(std::move(lhs)), m_RHS(std::move(rhs)) {}
	public:
		std::shared_ptr<Expr> m_LHS;
		std::shared_ptr<Expr> m_RHS;
	};

	struct HaltExpr : public Expr {};

}