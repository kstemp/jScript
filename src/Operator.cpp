#include "Operator.h"

Node* getOperatorNode(Node* arg1, Node* arg2, const OperatorType op) {

	switch (op) {
	case OperatorType::Assignment: {

		if (dynamic_cast<VariableNode*>(arg1) != nullptr)
			return new VarAssignNode(arg1, arg2);
		else
			throw Exception("non-assignable node!", -69);

	}
	case OperatorType::Equal:
		return new BinOpNode(std::equal_to<>(), arg1, arg2);
	case OperatorType::Smaller:
		return new BinOpNode(std::less<>(), arg1, arg2);
	case OperatorType::Greater:
		return new BinOpNode(std::greater<>(), arg1, arg2);
	case OperatorType::Add:
		return new BinOpNode(std::plus<>(), arg1, arg2);
	case OperatorType::Subtract:
		return new BinOpNode(std::minus<>(), arg1, arg2);
	case OperatorType::Multiply:
		return new BinOpNode(std::multiplies<>(), arg1, arg2);
	case OperatorType::Divide:
		return new BinOpNode([](Variable a1, Variable a2){

			if (a2.isZero())
				throw Exception("division by zero", -69);
			
			return a1 / a2; 
		}, arg1, arg2); // TODO again, check division by zero
	default:
		throw Exception("should not happen!"); //TODO can it happen or not?
	}

}