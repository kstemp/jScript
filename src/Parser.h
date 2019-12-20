#pragma once

#include <array>
#include <istream>
#include "expression.h"

#include "Node.h"
#include "Lexer.h"

const std::array<std::string, 6> RESERVED = { "global", "func", "var", "return", "while", "if" };

class Parser {

	size_t _pos = 0;

	void _checkReserved(const std::string& name) const {

		if (std::find(std::begin(RESERVED), std::end(RESERVED), name) != std::end(RESERVED))
			throw Exception("'" + name + "' is a reserved keyword and cannot be used as a name", -69);

	}

	std::string _peekToken() {
		return tokens[_pos];
	}

	void _eatToken(std::string expected) {

		if (tokens[_pos] != expected)
			throw Exception("expected " + expected + " instead of " + tokens[_pos]);

		_pos++;
		
	}

	Node* getBlock() {

		auto token = _peekToken();

		if (token == "func")
			return parseFunctionDeclaration();

		if (token == "return ")
			return parseReturnStatement();

		if (token == "while")
			return parseWhileStatement();

		if (token == "var ")
			return parseVariableDeclaration();

		auto expr = parseExpression();

		_eatToken(";");

		return expr;

	}

public:

	std::vector<std::string>& tokens;

	Parser(std::vector<std::string>& tokens) : tokens(tokens) {}

	std::vector<Node*> parse() {
		
		_pos = 0;

		std::vector<Node*> out;
		while (pos < tokens.size())
			out.push_back(getBlock());

		return out;

	}

	Node* parseReturnStatement();
	Node* parseFunctionDeclaration();
	Node* parseWhileStatement();
	Node* parseVariableDeclaration();

};