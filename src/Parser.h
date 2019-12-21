#pragma once

#include <array>

#include "Node.h"

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

	std::string _eatString() {

		// TODO check if has length 1
		// TODO this is not really readString, more like readAllowedName...

		if (!isalpha(tokens[_pos].at(0)))
			throw Exception("expected string not starting with whatever this one starts with");

		_pos++;
		return tokens[_pos - 1];

	}

	Node* _parseReturnStatement() {
		
		_eatToken("return");
		auto expr = _parseExpression();
		_eatToken(";");

		return new ReturnNode(expr);

	}

	Node* _parseWhileStatement() {

		_eatToken("while");
		_eatToken("(");

		WhileNode* out = new WhileNode();
		out->expr = _parseExpression();

		_eatToken(")");
		_eatToken("{");

		while (_peekToken() != "}")
			out->body.push_back(_getBlock());

		_eatToken("}");

		return out;

	}

	Node* _parseFunctionDeclaration() {

		_eatToken("func");

		const std::string functionName = _eatString();
		_checkReserved(functionName);

		FunctionNode* out = new FunctionNode(functionName);

		_eatToken("(");
		while (_peekToken() != ")") {
			out->parameters.push_back(_eatString());
			if (_peekToken() != ")")
				_eatToken(",");
		}

		_eatToken(")");
		_eatToken("{");

		while (_peekToken() != "}")
			out->body.push_back(_getBlock());

		_eatToken("}");

		return out;

	}

	Node* _parseVariableDeclaration() {

		_eatToken("var");

		std::string varName = _eatString();
		_checkReserved(varName);

		if (_peekToken() != "=") {
			_eatToken(";");
			return new VarDeclNode(varName);
		}

		_eatToken("=");
		auto valueExpr = _parseExpression();
		_eatToken(";");

		return new VarDeclNode(varName, valueExpr);

	}

	Node* _parseExpressionInternal() {

	}

	Node* _parsePrimaryExpression() {

	}

	Node* _parseExpression() {
		return _parseExpressionInternal(_parsePrimaryExpression(), 0);
	}

	Node* _getBlock() {

		auto token = _peekToken();

		if (token == "func")
			return _parseFunctionDeclaration();

		if (token == "return")
			return _parseReturnStatement();

		if (token == "while")
			return _parseWhileStatement();

		if (token == "var")
			return _parseVariableDeclaration();

		auto expr = _parseExpression();

		_eatToken(";");

		return expr;

	}

public:

	std::vector<std::string>& tokens;

	Parser(std::vector<std::string>& tokens) : tokens(tokens) {}

	std::vector<Node*> parse() {
		
		_pos = 0;

		std::vector<Node*> out;
		while (_pos < tokens.size())
			out.push_back(_getBlock());

		return out;

	}

};