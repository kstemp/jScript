/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Visitor.cpp
	@description:	Visitor pattern implementation.

*/

#include "RunVisitor.h"

void RunVisitor::visit(ValueNode& valueNode){
	result = valueNode._value;
}

void RunVisitor::visit(UnaryNode& unaryNode){
	unaryNode.arg->accept(this);
	result = unaryNode.function(result);
}

void RunVisitor::visit(VariableNode& variableNode){

	Scope& s = scopes[scopes.size() - 1 - variableNode.up];

		auto varit = s.variables.find(variableNode.varName);
		if (varit != s.variables.end()){

			//Console::writeLn("VariableNode: found variable '" + varName + "' = " + std::to_string(it->second->Int()) + " in scope '" + s->name + "' (we are in scope '" + currentScope->name + "')", Color::Yellow);
			variableNode.var = &varit->second;
			result = varit->second;

			return;

		}

	// Variable was not found in any enclosing scope
	throw Exception("variable '" + variableNode.varName + "' does not exist", -69);

}

void RunVisitor::visit(BinOpNode& binOpNode){

	binOpNode.arg1->accept(this);
	const Variable res1 = result;

	binOpNode.arg2->accept(this);
	const Variable res2 = result;

	result = binOpNode.function(res1, res2);

}

void RunVisitor::visit(VarAssignNode& varAssignNode){

	varAssignNode.arg1->accept(this);

	varAssignNode.arg2->accept(this);

	// we assign the evaluated node both to the Variable in question,
	// and this node. This allows us to have c = a = 56, for instance.
	*static_cast<VariableNode*>(varAssignNode.arg1)->var = result;

}

void RunVisitor::visit(WhileNode& whileNode){

	while (true) {

		whileNode.expr->accept(this);
		if (result.getData<int>()) {

			scopes.emplace_back(Scope());

			Variable temp;//TODO figure out a better method
			bool caught = false;

			try {

				for (const auto& jt : whileNode.body)
					jt->accept(this);

			}
			catch (Variable var) {
				caught = true;
				temp = var;
			}

			scopes.pop_back();

			if (caught)
				throw temp;

		}
		else break;
	}

}

void RunVisitor::visit(FunctionNode& functionNode){

	//TODO maybe we should have a derived GlobalScope : Scope instead...?
	if (scopes.back().name != "global")
		throw Exception("functions may only be declared in top-level (i.e. global) scope");

	methods[functionNode.name] = &functionNode;

}

void RunVisitor::visit(FuncCallNode& funcCallNode){

	auto it = methods.find(funcCallNode.name);

	Console::writeInfoLn("calling func " + funcCallNode.name, "info");

	if (it == methods.end())
		throw Exception("method '" + funcCallNode.name + "' does not exist", -69);

	if (it->second->parameters.size() != funcCallNode.arguments.size())
		throw Exception("invalid number: " + std::to_string(funcCallNode.arguments.size()) + " of arguments for function '" + funcCallNode.name + "' (expected " + std::to_string(it->second->parameters.size()) + ")", -69);

	std::vector<Variable> results;

	for (size_t i = 0; i < funcCallNode.arguments.size(); ++i){
		funcCallNode.arguments[i]->accept(this);
		results.push_back(result);
	}
	
	scopes.emplace_back(Scope(it->first));

	for (size_t i = 0; i < funcCallNode.arguments.size(); ++i) 
		scopes.back().variables[it->second->parameters[i]] = results[i];

	try{

		for (auto& jt : it->second->body)
			jt->accept(this);

	}
	catch (Variable var){
		//TODO val or ref???
		result = var;
	}

	scopes.pop_back();

}

void RunVisitor::visit(ReturnNode& returnNode){

	returnNode.expr->accept(this);
	throw result;

}

void RunVisitor::visit(VarDeclNode& varDeclNode){

	if (scopes.back().variables.count(varDeclNode.varName))
		throw Exception("variable '" + varDeclNode.varName + "' has already been declared in this scope");

	if (varDeclNode.valueExpr != nullptr){
		varDeclNode.valueExpr->accept(this);
		scopes.back().variables[varDeclNode.varName] = result;
	}
	else
		scopes.back().variables[varDeclNode.varName] = Variable();

}
