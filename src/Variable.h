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

#include "Exception.h"

enum class VarType {

	Double,
	Int,
	Undefined

};

union VarData {

	double Double;
	int Int;

};

struct Variable {

private:

	VarData _data;

	VarType _type;

public:


	double Double() const {
		
		switch (_type) {
		case VarType::Int:
			return static_cast<double>(_data.Int);
		case VarType::Double:
			return _data.Double;
		}
		
	}

	int Int() const {
		
		switch (_type) {
		case VarType::Int:
			return _data.Int;
		case VarType::Double:
			return static_cast<int>(_data.Double);
		}

	}

	// Returns the currently stored datatype
	const VarType type() const {
		return _type;
	}

	//	Default constructor. Assigns no numeric value and 
	//	sets type as Undefined
	Variable() : _type(VarType::Undefined) {
		std::cout << "VARIABLE created VOID\n";
	
	}

	//	Initializes Variable to a double value
	Variable(const double& val) : _type(VarType::Double) {
		_data.Double = val;
		std::cout << "VARIABLE created DOUBLE\n";
	}

	//	Copy constructor
	Variable(const Variable& var) : _type(var._type), _data(var._data) {}

	//	Initializes Variable to an integer value
	Variable(const int& val) : _type(VarType::Int) {
		_data.Int = val;
		std::cout << "VARIABLE created INT\n";
	}

	// Copy-assignment constructor
	Variable& operator = (const Variable& var) {

		_type = var._type;
		_data = var._data;
		return *this;

	}

	const bool isZero() const{
		switch (_type) {
		case VarType::Int:
			return _data.Int == int(0);
		case VarType::Double:
			return _data.Double == double(0);
		}
	}

	// Unary minus
	Variable operator - () {

		if (_type == VarType::Double)
			return Variable(-_data.Double);
		else if (_type == VarType::Int)
			return Variable(-_data.Int);
		else
			throw Exception("Undefined argument to numeric unary operator");

	}

	friend std::ostream& operator << (std::ostream& out, const Variable& var) {

		switch (var._type) {

		case VarType::Double:
			out << "[double] " << var._data.Double;
		break;

		case VarType::Int:
			out << "[int] " << var._data.Int;
		break;

		case VarType::Undefined:
			out << "[Undefined]";
		break;

		}

		return out;

	}

	~Variable() {

		std::cout << "VARIABLE DESTROYED!\n";
		// DEBUG PURPOSES
	}

};

//	Binary operators require both Variables to be of numeric type
inline void ensureNotUndefined(const Variable& v1, const Variable& v2) {

	if (v1.type() == VarType::Undefined || v2.type() == VarType::Undefined)
		throw Exception("Undefined argument to numeric binary operator");

}

template<typename OP>
inline Variable getVar(const Variable& v1, const Variable& v2, OP op)  {

	ensureNotUndefined(v1, v2);

	if (v1.type() == VarType::Double || v2.type() == VarType::Double)
		return Variable(op(v1.Double(), v2.Double()));

	return Variable(op(v1.Int(), v2.Int()));
	
};

Variable operator + (const Variable& v1, const Variable& v2);

Variable operator - (const Variable& v1, const Variable& v2);

Variable operator * (const Variable& v1, const Variable& v2);

Variable operator / (const Variable& v1, const Variable& v2);

Variable operator > (const Variable& v1, const Variable& v2);

Variable operator < (const Variable& v1, const Variable& v2);

Variable operator == (const Variable& v1, const Variable& v2);
