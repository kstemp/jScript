/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Visitor.h
	@description:	definition of Visitor class, which is reponsible for traversing the AST 
					and evaluating its nodes appropriately.

*/

#pragma once

class Visitor;

#include "Node.h"

class Visitor {

public:

	Variable result;

	void visitValueNode(ValueNode& valueNode);

	void visitUnaryNode(UnaryNode& unaryNode);

	void visitVariableNode(VariableNode& variableNode);

	void visitBinOpNode(BinOpNode& binOpNode);

	void visitVarAssignNode(VarAssignNode& varAssignNode);

	void visitWhileNode(WhileNode& whileNode);

	void visitFunctionNode(FunctionNode& functionNode);

	void visitFuncCallNode(FuncCallNode& funcCallNode);

	void visitReturnNode(ReturnNode& returnNode);

	void visitVarDeclNode(VarDeclNode& varDeclNode);

};