#include "Node.h"

void ValueNode::accept(Visitor* visitor) {
	visitor->visitValueNode(*this);
}

void UnaryNode::accept(Visitor* visitor) {
	visitor->visitUnaryNode(*this);
}

void VariableNode::accept(Visitor* visitor) {
	visitor->visitVariableNode(*this);
}

void BinOpNode::accept(Visitor* visitor) {
	visitor->visitBinOpNode(*this);
}


void VarAssignNode::accept(Visitor* visitor) {
	visitor->visitVarAssignNode(*this);
}


void WhileNode::accept(Visitor* visitor) {
	visitor->visitWhileNode(*this);
}


void FunctionNode::accept(Visitor* visitor) {
	visitor->visitFunctionNode(*this);
}

void FuncCallNode::accept(Visitor* visitor) {
	visitor->visitFuncCallNode(*this);
}


void ReturnNode::accept(Visitor* visitor) {
	visitor->visitReturnNode(*this);
}


void VarDeclNode::accept(Visitor* visitor) {
	visitor->visitVarDeclNode(*this);
}