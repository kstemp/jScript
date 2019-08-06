#include "Node.h"

void ValueNode::accept(Visitor* visitor) {
	visitor->visit(*this);
}

void UnaryNode::accept(Visitor* visitor) {
	visitor->visit(*this);
}

void VariableNode::accept(Visitor* visitor) {
	visitor->visit(*this);
}

void BinOpNode::accept(Visitor* visitor) {
	visitor->visit(*this);
}


void VarAssignNode::accept(Visitor* visitor) {
	visitor->visit(*this);
}


void WhileNode::accept(Visitor* visitor) {
	visitor->visit(*this);
}


void FunctionNode::accept(Visitor* visitor) {
	visitor->visit(*this);
}

void FuncCallNode::accept(Visitor* visitor) {
	visitor->visit(*this);
}


void ReturnNode::accept(Visitor* visitor) {
	visitor->visit(*this);
}


void VarDeclNode::accept(Visitor* visitor) {
	visitor->visit(*this);
}