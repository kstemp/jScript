/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Visitor.cpp
	@description:	Visitor pattern implementation.

*/

#include "Visitor.h"


void Visitor::visitValueNode(ValueNode& valueNode) {
	result = valueNode._value;
}

void Visitor::visitUnaryNode(UnaryNode& unaryNode) {
	unaryNode.arg->accept(this);
	result = unaryNode.function(result);
}

void Visitor::visitVariableNode(VariableNode& variableNode) {

	for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {

		auto varit = it->variables.find(variableNode.varName);
		if (varit != it->variables.end()) {

			//consoleWriteLn("VariableNode: found variable '" + varName + "' = " + std::to_string(it->second->Int()) + " in scope '" + s->name + "' (we are in scope '" + currentScope->name + "')", Color::Yellow);
			variableNode.var = &varit->second;
			result = varit->second;

			return;

		}
	}

	// Variable was not found in any enclosing scope
	throw Exception("variable '" + variableNode.varName + "' does not exist", -69);


}

void Visitor::visitBinOpNode(BinOpNode& binOpNode) {

	binOpNode.arg1->accept(this);
	Variable res1 = result;

	binOpNode.arg2->accept(this);
	Variable res2 = result;

	result = binOpNode.function(res1, res2);

}

void Visitor::visitVarAssignNode(VarAssignNode& varAssignNode) {

	varAssignNode.arg1->accept(this);

	varAssignNode.arg2->accept(this);

	//arg1->a

	// we assign the evaluated node both to the Variable in question,
	// and this node. This allows us to have c = a = 56, for instance.
	*static_cast<VariableNode*>(varAssignNode.arg1)->var = result;

	//return value;

}

void Visitor::visitWhileNode(WhileNode& whileNode) {

	while (true) {

		whileNode.expr->accept(this);

		if (!result.getData<int>())
			break;

		scopes.push_back(Scope());

		try {

			for (auto&jt : whileNode.body)
				jt->accept(this);


		}
		catch (Variable var) {
			scopes.pop_back();
			throw;
		}

	}

}

void Visitor::visitFunctionNode(FunctionNode& functionNode) {

	//TODO maybe we should have a derived GlobalScope : Scope instead...?
	if (scopes.back().name != "global")
		throw Exception("functions may only be declared in top-level (i.e. global) scope");

	methods[functionNode.name] = &functionNode;

}

void Visitor::visitFuncCallNode(FuncCallNode& funcCallNode) {

	auto it = methods.find(funcCallNode.name);

	if (it == methods.end())
		throw Exception("method '" + funcCallNode.name + "' does not exist", -69);

	if (it->second->parameters.size() != funcCallNode.arguments.size())
		throw Exception("invalid number: " + std::to_string(funcCallNode.arguments.size()) + " of arguments for function '" + funcCallNode.name + "' (expected " + std::to_string(it->second->parameters.size()) + ")", -69);

	scopes.push_back(Scope(it->first));

	for (size_t i = 0; i < funcCallNode.arguments.size(); ++i) {
		funcCallNode.arguments[i]->accept(this);
		scopes.back().variables[it->second->parameters[i]] = result;
 	}

	try {

		for (auto&jt : it->second->body)
			jt->accept(this);

	}
	catch (Variable var) {
		result = var;
	}

	scopes.pop_back();

}

void Visitor::visitReturnNode(ReturnNode& returnNode) {

	returnNode.expr->accept(this);
	throw result;

}

void Visitor::visitVarDeclNode(VarDeclNode& varDeclNode) {

	if (scopes.back().variables.count(varDeclNode.varName))
		throw Exception("variable '" + varDeclNode.varName + "' has already been declared in this scope");

	if (varDeclNode.valueExpr != nullptr) {
		varDeclNode.valueExpr->accept(this);
		scopes.back().variables[varDeclNode.varName] = result;
	}
	else
		scopes.back().variables[varDeclNode.varName] = Variable();

}