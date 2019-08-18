#include "Node.h"

void ValueNode::accept(NodeVisitor* visitor) {
	visitor->visit(*this);
}

void UnaryNode::accept(NodeVisitor* visitor) {
	visitor->visit(*this);
}

void VariableNode::accept(NodeVisitor* visitor) {
	visitor->visit(*this);
}

void BinOpNode::accept(NodeVisitor* visitor) {
	visitor->visit(*this);
}

void VarAssignNode::accept(NodeVisitor* visitor) {
	visitor->visit(*this);
}

void WhileNode::accept(NodeVisitor* visitor) {
	visitor->visit(*this);
}

void FunctionNode::accept(NodeVisitor* visitor) {
	visitor->visit(*this);
}

void FuncCallNode::accept(NodeVisitor* visitor) {
	visitor->visit(*this);
}

void ReturnNode::accept(NodeVisitor* visitor) {
	visitor->visit(*this);
}

void VarDeclNode::accept(NodeVisitor* visitor) {
	visitor->visit(*this);
}
