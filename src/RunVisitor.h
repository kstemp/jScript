/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Visitor.h
	@description:	definition of Visitor class, which is reponsible for traversing the AST 
					and evaluating its nodes appropriately.

*/

#pragma once

#include "NodeVisitor.h"

struct RunVisitor : NodeVisitor {

	Variable result;

	void visit(ValueNode& node) override;
	void visit(UnaryNode& node) override;
	void visit(VariableNode& node) override;
	void visit(BinOpNode& node) override;
	void visit(VarAssignNode& node) override;
	void visit(WhileNode& node) override;
	void visit(FunctionNode& node) override;
	void visit(FuncCallNode& node)  override;
	void visit(ReturnNode& node) override;
	void visit(VarDeclNode& node) override;

};
