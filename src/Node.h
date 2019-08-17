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
struct ValueNode;
struct VariableNode;
struct UnaryNode;
struct BinOpNode;
struct WhileNode;
struct FunctionNode;
struct FuncCallNode;
struct VarAssignNode;
struct VarDeclNode;
struct ReturnNode;
struct FunctionNode;

#include "Visitor.h"
#include "Resolver.h"

extern std::deque<Scope> scopes;

extern std::unordered_map<std::string, FunctionNode*> methods;

/*

	Node

	@description: abstract base class, representing a single node of an AST.

*/
struct Node {

	public:

		Node(){}

		virtual void accept(Visitor* visitor) = 0;
		virtual void accept(Resolver* resolver) = 0;
		
		virtual ~Node(){}

};

/*

	ValueNode

	@description: represents a numeric literal such as 7672.3

*/
struct ValueNode : public Node {

public:

	const Variable _value;

	template<typename T>
	ValueNode(const T val) : _value(val) {} 

	void accept(Visitor* visitor);
	void accept(Resolver* resolver);

	~ValueNode() {}

};

/*

	UnaryNode

	@description: represents an unary operations like -(expr).

*/
struct UnaryNode : public Node {

private:


public:


	Node* arg;

	const std::function<Variable(const Variable&)> function;

	UnaryNode(const std::function<Variable(const Variable&)> function, Node* arg)
		: function(function), arg(arg) {}

	void accept(Visitor* visitor);
	void accept(Resolver* resolver);

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



public:

	void setUp(int _up) {
		up = _up;
	}

	int up;

	const std::string varName;

	Variable* var;

	VariableNode(const std::string name)
		: varName(name) {}

	void accept(Visitor* visitor);
	void accept(Resolver* resolver);

};

/*

	BinOpNode

	@description: used for binary operations such as expr1 + expr2, or expr1 >= expr2.

*/
struct BinOpNode : public Node {

public:


	Node* arg1;
	Node* arg2;

	const std::function<Variable(const Variable&, const Variable&)> function;

	BinOpNode(std::function<Variable(const Variable&, const Variable&)> function, Node* arg1, Node* arg2) 
		: function(function), arg1(arg1), arg2(arg2) {}


	void accept(Visitor* visitor);	
	void accept(Resolver* resolver);

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

public:

	Node* arg1;
	Node* arg2;


	VarAssignNode(Node* arg1, Node* arg2) : arg1(arg1), arg2(arg2) {}

	void accept(Visitor* visitor);
	void accept(Resolver* resolver);

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

	void accept(Visitor* visitor);
	void accept(Resolver* resolver);

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




public:

	const std::string name;

	//TODO there should be a way to lock parameters/body after the function was declared
	std::vector<std::string> parameters;

	std::vector<Node*> body;

	FunctionNode(const std::string name) : name(name) {}

	void accept(Visitor* visitor);
	void accept(Resolver* resolver);

	~FunctionNode(){
		
		for (auto& it : body)
			delete it;

	}

};

struct FuncCallNode : Node {

	const std::string name;

	std::vector<Node*> arguments;

	FuncCallNode(const std::string name) : name(name) {}

	void accept(Visitor* visitor);
	void accept(Resolver* resolver);

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


public:


	Node* expr;

	ReturnNode(Node* expr) : expr(expr) {}

	void accept(Resolver* resolver);
	void accept(Visitor* visitor);

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

public:

	const std::string varName;
	Node* valueExpr;


	VarDeclNode(const std::string varName, Node* valueExpr = nullptr)
		: varName(varName), valueExpr(valueExpr) {}

	void accept(Visitor* visitor);
	void accept(Resolver* resolver);
};