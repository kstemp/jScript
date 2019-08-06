/*

	jScript
	copyright (C) 2019 K. Stempinski

*/

#include "Resolver.h"

template<>
void Resolver::visit(ValueNode& valueNode) {
	// do nothing
}

template<>
void Resolver::visit(UnaryNode& unaryNode) {
	unaryNode.accept(this);
}

template<>
void Resolver::visit(VariableNode& variableNode) {

	for (auto i = scopes.size() - 1; i >= 0; --i) {

		auto varit = scopes.at(1).variables.find(variableNode.varName);
		if (varit != it->variables.end()) {

			//Console::writeLn("VariableNode: found variable '" + varName + "' = " + std::to_string(it->second->Int()) + " in scope '" + s->name + "' (we are in scope '" + currentScope->name + "')", Color::Yellow);
			variableNode.var = &varit->second;
			result = varit->second;

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

}

template<>
void Resolver::visit(WhileNode& whileNode) {

	scopes.emplace_back(Scope("while block"));
	//
	for (const auto& jt : whileNode.body)
		jt->accept(this);
	//
	scopes.pop_back();

}

template<>
void Resolver::visit(FunctionNode& functionNode) {

	scopes.emplace_back(Scope(functionNode.name));
	//



	//
	scopes.pop_back();

}

template<>
void Resolver::visit(FuncCallNode& funcCallNode) {

}

template<>
void Resolver::visit(ReturnNode& returnNode) {

}

template<>
void Resolver::visit(VarDeclNode& varDeclNode) {

}
