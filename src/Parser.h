#pragma once

#include <array>

#include "Node.h"

const std::array<std::string, 6> RESERVED = { "global", "func", "var", "return", "while", "if" };

class Parser {

	size_t _pos = 0;

	void _checkReserved(const std::string& name) const {

		if (std::find(std::begin(RESERVED), std::end(RESERVED), name) != std::end(RESERVED))
			throw Exception("'" + name + "' is a reserved keyword and cannot be used as a name", _pos);

	}

	std::string _peekToken() {
		// TODO EMPTY_TOKEN type
		return _pos < tokens.size() ? tokens[_pos] : "EMPTY_TOKEN";
	}

	void _eatToken(std::string expected) {

		if (tokens[_pos] != expected)
			throw Exception("expected " + expected + " instead of " + tokens[_pos], _pos);

		_pos++;
		
	}

	std::string _eatString() {

		// TODO check if has length 1
		// TODO this is not really readString, more like readAllowedName...

		if (!isalpha(tokens[_pos].at(0)))
			throw Exception("expected string not starting with whatever this one starts with", _pos);

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

	bool _isBinaryOperator(std::string token) {
		return token == "+" || token == "*";
	}

	std::unordered_map<std::string, int> PREC = {
		{ "+",  1 },
		{ "*",  1 }
	};

	Node* _parseExpressionInternal(Node* lhs, int minPrecedence) {
		std::string lookahead = _peekToken();

		while (_isBinaryOperator(lookahead) && PREC[lookahead] >= minPrecedence) {

			std::string op = lookahead;

			_eatToken(lookahead);

			Node* rhs = _parsePrimaryExpression();

			lookahead = _peekToken();

			while (_isBinaryOperator(lookahead) && PREC[lookahead] > PREC[op]) {

				rhs = _parseExpressionInternal(rhs, PREC[lookahead]);

				lookahead = _peekToken();

			}

			lhs = new BinOpNode([](Variable b, Variable c) { return (b + c);  }, lhs, rhs);

		}

		return lhs;
	}

	Node* _parsePrimaryExpression() {
		_eatToken("2");
		return new ValueNode(2);
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