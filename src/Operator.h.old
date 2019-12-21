#pragma once

#include <unordered_map>

#include "Node.h"

enum class OperatorType {

	None,
	Assignment,
	Add,
	Subtract,
	Multiply,
	Divide,
	Greater,
	Smaller,
	Equal

};

enum class Associativity {

	Left,
	Right

};


struct OperatorValue {

	const OperatorType op;
	Node* value;
	OperatorValue(const OperatorType opr, Node* val) 
		: op(opr), value(val) { }

	const bool isNull() const { 
		return op == OperatorType::None;
	}
};

const std::unordered_map<OperatorType, int> PRECEDENCE = {	{ OperatorType::Assignment,		4 },
														{ OperatorType::Equal,			5 },
														{ OperatorType::Smaller,		6 },
														{ OperatorType::Greater,		6 },
														{ OperatorType::Add,			10 },
														{ OperatorType::Subtract,		10 },
														{ OperatorType::Divide,			20 },
														{ OperatorType::Multiply,		20 },
														{ OperatorType::None,			0 } };

const std::unordered_map<OperatorType, Associativity> ASSOCIATIVITY = {	{ OperatorType::Assignment,		Associativity::Right },
																	{ OperatorType::Equal,			Associativity::Left  },
																	{ OperatorType::Smaller,		Associativity::Left  },
																	{ OperatorType::Greater,		Associativity::Left  },
																	{ OperatorType::Add,			Associativity::Left  },
																	{ OperatorType::Subtract,		Associativity::Left  },
																	{ OperatorType::Divide,			Associativity::Left  },
																	{ OperatorType::Multiply,		Associativity::Left  },
																	{ OperatorType::None,			Associativity::Left } };


Node* getOperatorNode(Node* arg1, Node* arg2, const OperatorType op);