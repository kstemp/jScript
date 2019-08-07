/*

	jScript
	copyright (C) 2019 K. Stempinski

*/

#include "Resolver.h"

//TODO dedicated methods for creating new scope or removing one

template<>
void Resolver::visit(ValueNode& valueNode) {
	// do nothing
}

template<>
void Resolver::visit(UnaryNode& unaryNode) {
	unaryNode.arg->accept(this);
}

template<>
void Resolver::visit(VariableNode& variableNode) {

	for (int i = scopes.size() - 1; i >= 0; i -= 1) {

		auto varit = scopes.at(i).variables.find(variableNode.varName);
		if (varit != scopes.at(i).variables.end()) {

			int up = scopes.size() - 1 - i;

			Console::writeLn("VariableNode: found variable '" + variableNode.varName + " in scope '" + scopes.at(i).name + "', which is " + std::to_string(up) + " scopes up", Color::yellow);
			variableNode.up = up;

			return;

		}
	}

	// Variable was not found in any enclosing scope
	throw Exception("variable '" + variableNode.varName + "' does not exist", -69);

}

template<>
void Resolver::visit(BinOpNode& binOpNode) {
	binOpNode.arg1->accept(this);
	binOpNode.arg2->accept(this);
}

template<>
void Resolver::visit(VarAssignNode& varAssignNode) {
	//TODO implement
}

template<>
void Resolver::visit(WhileNode& whileNode) {

	scopes.emplace_back(Scope("while block"));
	//
	for (const auto& it : whileNode.body)
		it->accept(this);
	//
	scopes.pop_back();

}

template<>
void Resolver::visit(FunctionNode& functionNode) {

	scopes.emplace_back(Scope(functionNode.name));
	//
	for (size_t i = 0; i < functionNode.parameters.size(); ++i) 
		scopes.back().variables[functionNode.parameters[i]] = Variable(); //TODO what value?

	for (const auto& it : functionNode.body)
		it->accept(this);
	//
	scopes.pop_back();

}

template<>
void Resolver::visit(FuncCallNode& funcCallNode) {
	
	for (const auto& it : funcCallNode.arguments)
		it->accept(this);

}

template<>
void Resolver::visit(ReturnNode& returnNode) {
	returnNode.expr->accept(this);
}

template<>
void Resolver::visit(VarDeclNode& varDeclNode) {

	if (scopes.back().variables.count(varDeclNode.varName))
		throw Exception("variable '" + varDeclNode.varName + "' has already been declared in this scope");

	scopes.back().variables[varDeclNode.varName] = Variable();

}
