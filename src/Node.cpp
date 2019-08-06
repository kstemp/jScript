#include "Node.h"

void ValueNode::accept(Visitor* resolver) {
	resolver->visit(*this);
}

void UnaryNode::accept(Visitor* resolver) {
	resolver->visit(*this);
}

void VariableNode::accept(Visitor* resolver) {
	resolver->visit(*this);
}

void BinOpNode::accept(Visitor* resolver) {
	resolver->visit(*this);
}


void VarAssignNode::accept(Visitor* resolver) {
	resolver->visit(*this);
}


void WhileNode::accept(Visitor* resolver) {
	resolver->visit(*this);
}


void FunctionNode::accept(Visitor* resolver) {
	resolver->visit(*this);
}

void FuncCallNode::accept(Visitor* resolver) {
	resolver->visit(*this);
}


void ReturnNode::accept(Visitor* resolver) {
	resolver->visit(*this);
}


void VarDeclNode::accept(Visitor* resolver) {
	resolver->visit(*this);
}

//// 
///
///

void ValueNode::accept(Resolver* resolver) {
resolver->visit(*this);
}

void UnaryNode::accept(Resolver* resolver) {
	resolver->visit(*this);
}

void VariableNode::accept(Resolver* resolver) {
	resolver->visit(*this);
}

void BinOpNode::accept(Resolver* resolver) {
	resolver->visit(*this);
}


void VarAssignNode::accept(Resolver* resolver) {
	resolver->visit(*this);
}


void WhileNode::accept(Resolver* resolver) {
	resolver->visit(*this);
}


void FunctionNode::accept(Resolver* resolver) {
	resolver->visit(*this);
}

void FuncCallNode::accept(Resolver* resolver) {
	resolver->visit(*this);
}


void ReturnNode::accept(Resolver* resolver) {
	resolver->visit(*this);
}


void VarDeclNode::accept(Resolver* resolver) {
	resolver->visit(*this);
}