#pragma once

struct NodeVisitor;

#include "Node.h"

struct NodeVisitor {

	virtual void visit(ValueNode& node) = 0;
	virtual void visit(UnaryNode& node) = 0;
	virtual void visit(VariableNode& node) = 0;
	virtual void visit(BinOpNode& node) = 0;
	virtual void visit(VarAssignNode& node) = 0;
	virtual void visit(WhileNode& node) = 0;
	virtual void visit(FunctionNode& node) = 0;
	virtual void visit(FuncCallNode& node) = 0;
	virtual void visit(ReturnNode& node) = 0;
	virtual void visit(VarDeclNode& node) = 0;

};