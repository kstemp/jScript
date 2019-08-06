#pragma once

#include <stack>
#include <iostream>

#include "Lexer.h"
#include "Operator.h"

struct Parser {

	const std::vector<std::string> RESERVED = { "global", "func", "var", "return", "while", "if" };

	inline void checkReserved(const std::string& name) {

		if (std::find(std::begin(RESERVED), std::end(RESERVED), name) != std::end(RESERVED))
			throw Exception("'" + name + "' is a reserved keyword and cannot be used as a name", lexer.gpos());

	}

	Lexer& lexer;

	void parse(std::vector<Node*>& program) {

		//TODO we shoud not be using eof here
		while (!lexer.eof())
			program.push_back(getBlock());

	}

	std::stack<OperatorValue> stack;

	Parser(Lexer& lexer) : lexer(lexer) {}

	Node* parseReturnStatement();
	Node* parseFunctionDeclaration();
	Node* parseWhileStatement();
	Node* parseVariableOrFunction();
	Node* parseVariableDeclaration();
	Node* parseValueNode();

	Node* getBlock() {

		lexer.skipSpacesTabsNewlines();

		if (lexer.peek("func "))
			return parseFunctionDeclaration();
		
		if (lexer.peek("return ")) 
			return parseReturnStatement();
		
		if (lexer.peek("while ")) 
			return parseWhileStatement();
		
		if (lexer.peek("var ")) 
			return parseVariableDeclaration();

		try {
				Node* expr = parseExpression();
				
				lexer.eat(";");
				return expr;

			} catch (Exception& e) // TODO exceptions
			{

				while (!stack.empty())
					stack.pop();
				throw e;
			}

	}

	/*

		OperatorType parseBinaryOperator()

		@description:
		@returns:

	*/
	OperatorType parseBinaryOperator() {

		lexer.skipSpacesTabsNewlines();

		OperatorType returnVal = OperatorType::None;

		switch (lexer.current()) {
		case '=':
			lexer.advance();
			if (lexer.current() != '=')
				return OperatorType::Assignment;
			lexer.advance();
			return OperatorType::Equal;
		case '<':
			lexer.advance();
			return OperatorType::Smaller;
		case '>':
			lexer.advance();
			return OperatorType::Greater;
		case '+':
			lexer.advance();
			return OperatorType::Add;
		case '-':
			lexer.advance();
			return OperatorType::Subtract;
		case '/':
			lexer.advance();
			return OperatorType::Divide;
		case '*':
			lexer.advance();
			return OperatorType::Multiply;
		default:
			return OperatorType::None;

		}

	}

	/*

		Node* parseValue()

		@description: TODO

	*/
	Node* parseValue() {

		lexer.skipSpacesTabsNewlines();

		if (isdigit(lexer.current()))
			return parseValueNode();

		char p = lexer.current();
		switch (p) {

		case '(': {

			lexer.advance();

			Node* expr = parseExpression();


			lexer.eat(")");
			//if (!lexer.peek(")"))
			//	throw Exception("expected ')' at the end of an expression", lexer.pos());

			//lexer.advance();
			return expr;
		}

		case '+':
			lexer.advance();
			return parseValue();

		case '-':
			lexer.advance();
			return new UnaryNode([](Variable i) { return -i; }, parseValue());

		default:

			if (isalpha(lexer.current()))
				return  parseVariableOrFunction();
	
			
			throw Exception("failed to parse expression", lexer.gpos());

			
		}
	}

	/*

		Node* parseExpression()

		@description: 

	*/
	Node* parseExpression() {

		stack.push(OperatorValue(OperatorType::None, 0));

		Node* value = parseValue();

		while (!stack.empty()) {

			OperatorType op(parseBinaryOperator());
			while (PRECEDENCE.at(op) < PRECEDENCE.at(stack.top().op) || (PRECEDENCE.at(op) == PRECEDENCE.at(stack.top().op) && ASSOCIATIVITY.at(op) == Associativity::Left)) {

				if (stack.top().isNull()) {
					stack.pop();
					return value;
				}

				value = getOperatorNode(stack.top().value, value, stack.top().op);
				stack.pop();

			}

		
			stack.push(OperatorValue(op, value));
			
			value = parseValue();

		}

		//TODO this is never hit, hmmm
		return 0;

	}

};