#pragma once

#include <array>
#include <istream>
#include "expression.h"

#include "Node.h"
#include "Lexer.h"

const std::array<std::string, 6> RESERVED = { "global", "func", "var", "return", "while", "if" };

struct Parser {

	Lexer& lexer;

	ExpressionParser exprParser;

	void checkReserved(const std::string& name) const {

		if (std::find(std::begin(RESERVED), std::end(RESERVED), name) != std::end(RESERVED))
			throw Exception("'" + name + "' is a reserved keyword and cannot be used as a name", lexer.pos());

	}

	void parse(std::vector<Node*>& program) {

		//TODO we shoud not be using eof here
		while (!lexer.eof())
			program.push_back(getBlock());

	}



	Parser(Lexer& lexer) : lexer(lexer), exprParser(lexer) {}

	Node* parseReturnStatement();
	Node* parseFunctionDeclaration();
	Node* parseWhileStatement();
	Node* parseVariableDeclaration();

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
				Node* expr = exprParser.parseExpression();
				
				lexer.eat(";");
				return expr;

			} catch (Exception& e) // TODO exceptions
			{

			

				while (!exprParser.stack.empty())
					exprParser.stack.pop();
				throw e;
			}

	}

};