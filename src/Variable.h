/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Variable.h
	@description:	Implements a dynamic type Variable, which can store double or int values
					(or be undefined). Variable is promoted according to the simple rule
					that if any of the operands is of type Double, everything else gets promoted to Double.
					However, if any of the operands is Undefined, an exception is thrown.

*/
#pragma once

#include <iostream>
#include <variant>
#include <functional>

#include "Exception.h"

template<class... Ts>
struct OverloadedVisitor : Ts... {
	using Ts::operator()...;
};

template<class... Ts> OverloadedVisitor(Ts...)->OverloadedVisitor<Ts...>;

//TODO check that types of G and Ts are the same (static_assert, is_same(_v) and enable_if, perhaps?)
template<typename G, typename... Ts>
bool isAnyEqualTo(G arg1, Ts... args) {
	return ((arg1 == args) || ...);
}

struct Variable {

	std::variant<std::monostate, int, double> data;

	const bool isUndefined() const {
		return data.index() == 0;
	}

	template<typename T>
	const T getData() const {

		// static cast to the same type CAN introduce some overhead, so first check whether we hold T,
		// (it's just faster than doing static_Cast to T from T)
		if (std::holds_alternative<T>(data))
			return std::get<T>(data);

		return std::visit(
			OverloadedVisitor{
				[](const auto& val) -> T { return static_cast<T>(val); },
				//NOTE we need this -> T here, otherwise compiler is unhappy...
				[](const std::monostate) -> T { throw Exception("variable is undefined and holds no data"); }
			},
			data);

	}

	//TODO assert that T is numeric, or something like that
	template<typename T>
	Variable(const T& val) : data(val) {
		//TODO debug only
		std::cout << "Variable created: " << typeid(T).name() << "\n";
	}

	// data is set to std::monostate, since Variable is of "undefined" type
	Variable() {
		std::cout << "VARIABLE created VOID\n";
	}

	Variable(const Variable& var) : data(var.data) {}

	Variable& operator = (const Variable& var) {

		data = var.data;
		return *this;

	}

	//TODO check if this really works? ==0 looks kinda dodgy
	const bool isZero() const {

		return std::visit(
			OverloadedVisitor{
				[](const auto& val) -> bool { return val == 0; },
				[](const std::monostate) -> bool { throw Exception("variable is undefined (thrown by IsZero)"); }
			},
			data);

	}

	Variable operator - () {

		return std::visit(
			OverloadedVisitor{
				[](const auto& val) -> Variable { return Variable(-val); },
				[](const std::monostate) -> Variable { throw Exception("undefined argument to unary - operator"); }
			},
			data);

	}

	friend std::ostream& operator << (std::ostream& out, const Variable& var) {

		return std::visit(
			OverloadedVisitor{
				[&](const auto& val) -> std::ostream & {
					out << "[" << typeid(val).name() << "] " << val;
					return out;
				},
				[&](const std::monostate) -> std::ostream & {
					out << "[undefined]";
					return out;
				}
			},
			var.data);

	}

	~Variable() {
		std::cout << "Destroyed variable of type TODO\n";
	}

};

template<typename OP>
inline Variable getVar(const Variable& v1, const Variable& v2, OP op) {

	return std::visit(OverloadedVisitor{
		[](std::monostate, std::monostate) -> Variable { throw Exception("undefined argument passed to numeric binary operator"); },
		[](auto, std::monostate) -> Variable { throw Exception("undefined argument passed to numeric binary operator"); },
		[](std::monostate, auto) -> Variable { throw Exception("undefined argument passed to numeric binary operator"); },
		[op](const auto a, const auto b) -> Variable { return Variable(op(a, b));  }
		}, v1.data, v2.data);

};

inline Variable operator + (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 + a2; });
}

inline Variable operator - (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 - a2; });
}

inline Variable operator * (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 * a2; });
}

inline Variable operator / (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 / a2; });
}

inline Variable operator > (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 > a2; });
}

inline Variable operator < (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 < a2; });
}

inline Variable operator == (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 == a2; });
}
