/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Node.h
	@description:	TODO

*/

#pragma once

#include <deque>
#include <unordered_map>
#include <functional>
#include <iostream>

#include "Variable.h"
#include "Scope.h"

struct Node;

extern std::deque<Scope> scopes;

struct FunctionNode;

extern std::unordered_map<std::string, FunctionNode*> methods;

/*

	Node

	@description: abstract base class, representing a single node of an AST.

*/
struct Node {

	public:

		Node(){}

		virtual Variable visit() = 0;
		
		virtual ~Node(){}

};

/*

	ValueNode

	@description: represents a numeric literal such as 7672.3

*/
struct ValueNode : public Node {

private:

	const Variable _value;

public:

	template<typename T>
	ValueNode(const T val) : _value(val) {} 

	Variable visit() { 
		return _value;
	}

	~ValueNode() {}

};

/*

	UnaryNode

	@description: represents an unary operations like -(expr).

*/
struct UnaryNode : public Node {

private:

	Node* arg;

	const std::function<Variable(const Variable&)> function;

public:

	UnaryNode(const std::function<Variable(const Variable&)> function, Node* arg)
		: function(function), arg(arg) {}

	Variable visit() {
		return function(arg->visit());
	}

	~UnaryNode() {
		delete arg;
	}

};

/*

	VariableNode

	@description: returns a reference to a variable of name varName found in the closest scope

*/
struct VariableNode : Node {

private:

	const std::string varName;

	Variable* var;

public:

	VariableNode(const std::string name)
		: varName(name) {}

	Variable visit() {

		for (auto it = scopes.rbegin(); it != scopes.rend(); ++it){

			auto varit = it->variables.find(varName);
			if (varit != it->variables.end()) {

				//consoleWriteLn("VariableNode: found variable '" + varName + "' = " + std::to_string(it->second->Int()) + " in scope '" + s->name + "' (we are in scope '" + currentScope->name + "')", Color::Yellow);
				var = &varit->second;
				return varit->second;

			}		
		}

		// Variable was not found in any enclosing scope
		throw Exception("variable '" + varName + "' does not exist", -69);

	}

	Variable* varPtr() {
		visit();
		return var;
	}

};

/*

	BinOpNode

	@description: used for binary operations such as expr1 + expr2, or expr1 >= expr2.

*/
struct BinOpNode : public Node {

protected:

	Node* arg1;
	Node* arg2;

	const std::function<Variable(const Variable&, const Variable&)> function;

public:

	BinOpNode(std::function<Variable(const Variable&, const Variable&)> function, Node* arg1, Node* arg2) 
		: function(function), arg1(arg1), arg2(arg2) {}

	Variable visit() {

		return getVar(arg1->visit(), arg2->visit(), function);
		//return function(arg1->visit(), arg2->visit());
	}

	~BinOpNode() {
		delete arg1;
		delete arg2;
	}

};

/*

	VarAssignNode

	@description:	

*/
struct VarAssignNode : Node{

private:

	Node* arg1;
	Node* arg2;

public:

	VarAssignNode(Node* arg1, Node* arg2) : arg1(arg1), arg2(arg2) {}

	Variable visit() {

		Variable value = arg2->visit();

		// we assign the evaluated node both to the Variable in question,
		// and this node. This allows us to have c = a = 56, for instance.
		*static_cast<VariableNode*>(arg1)->varPtr() = value;

		return value;

	}

	~VarAssignNode() {
		delete arg1;
		delete arg2;
	}

};

struct WhileNode : Node {

	Node* expr;

	std::vector<Node*> body;

	WhileNode() {}

public:

	Variable visit() {

		while (true) {

			if (!expr->visit().Int())
				break;

			scopes.push_back(Scope());

			try {
			
				for (auto&jt : body)
					jt->visit();

			
			} catch (Variable var) {
				scopes.pop_back();
				throw;
			}	

		}


	}

	~WhileNode() {
		body.clear();
		delete expr;
	}

};

/*

	FunctionNode

	@syntax:		
	@description: visit() declares a function, i.e. adds an entry to extern map methods[...]

*/
struct FunctionNode : Node{

private:

	const std::string name;


public:

	//TODO there should be a way to lock parameters/body after the function was declared
	std::vector<std::string> parameters;

	std::vector<Node*> body;

	FunctionNode(const std::string name) : name(name) {}

	Variable visit(){

		//TODO maybe we should have a derived GlobalScope : Scope instead...?
		if (scopes.back().name != "global")
			throw Exception("functions may only be declared in top-level (i.e. global) scope");

		methods[name] = this;

	}

	~FunctionNode(){
		
		for (auto& it : body)
			delete it;

	}

};

struct FuncCallNode : Node {

	const std::string name;

	std::vector<Node*> arguments;

	FuncCallNode(const std::string name) : name(name) {}

	Variable visit() {

		auto it = methods.find(name);

		if (it == methods.end())
			throw Exception("method '" + name + "' does not exist", -69);

		if (it->second->parameters.size() != arguments.size())
			throw Exception("invalid number: " + std::to_string(arguments.size()) + " of arguments for function '" + name + "' (expected " + std::to_string(it->second->parameters.size()) + ")", - 69);

		scopes.push_back(Scope(it->first));
		
		for (size_t i = 0; i < arguments.size(); ++i) 			
			scopes.back().variables[it->second->parameters[i]] = arguments[i]->visit();

		try {

			for (auto&jt : it->second->body)
				jt->visit();
					
		} catch (Variable var) {
			scopes.pop_back();
			return var;
		}


	}

};

/*

	ReturnNode

	@syntax:		return [expr];
	@description:	when visited,  evaluates [expr] and throws
					the variable that [expr] was evaluated to.
					The variable is then catched by FunctionBlock.

*/
struct ReturnNode : Node {

private:

	Node* expr;

public:

	ReturnNode(Node* expr) : expr(expr) {}

	Variable visit() {

		throw expr->visit();

	}

};

/*

	VarDeclNode

	@syntax:		var [name];
	@description:	when visited, looks through enclosing scopes, 
					and if a variable of name varName is not found,
					declares a variable of this name and type Undefined in the current scope

*/
struct VarDeclNode : Node {

private:

	const std::string varName;
	Node* valueExpr;

public:

	VarDeclNode(const std::string varName, Node* valueExpr = nullptr)
		: varName(varName), valueExpr(valueExpr) {}

	Variable visit() {

		if (scopes.back().variables.count(varName))
			throw Exception("variable '" + varName + "' has already been declared in this scope");

		if (valueExpr != nullptr)
			scopes.back().variables[varName] = valueExpr->visit();
		else 
			scopes.back().variables[varName] = Variable();
		
	}

};