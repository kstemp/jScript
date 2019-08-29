/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Block.cpp
	@description:	TODO

*/

#include "Parser.h"

/*

	Node* parseReturnStatement()

	@description: ^^

*/
Node* Parser::parseReturnStatement() {

	lexer.eat("return ");

	auto expr = exprParser.parseExpression();

	lexer.eat(";");

	return new ReturnNode(expr);

}

/*

	Node* parseWhileStatement()

	@description: ^^

*/
Node* Parser::parseWhileStatement() {

	lexer.eat("while ");

	lexer.eat("(");

	WhileNode* out = new WhileNode();

	out->expr = exprParser.parseExpression();

	lexer.eat(")");

	lexer.eat("{");

	while (!lexer.peek("}"))
		out->body.push_back(getBlock());

	lexer.eat("}");

	return out;

}

/*

	Node* parseFunctionDeclaration()

	@description: ^^

*/
Node* Parser::parseFunctionDeclaration() {

	lexer.eat("func ");

	const std::string functionName = lexer.readString();

	checkReserved(functionName);

	FunctionNode* out = new FunctionNode(functionName);

	lexer.eat("(");
	while (!lexer.peek(")")) {

		lexer.skipSpacesTabsNewlines();

		out->parameters.push_back(lexer.readString());
		if (!lexer.peek(")"))
			lexer.eat(",");

	}

	lexer.eat(")");
	lexer.eat("{");

	while (!lexer.peek("}"))
		out->body.push_back(getBlock());
	
	lexer.eat("}");

	return out;

}

/*

	Node* parseVariableDeclaration()

	@description:	parses variable declarations, of the form:

					var name;

	@returns:		pointer to a newly created VarDeclNode

*/
Node* Parser::parseVariableDeclaration() {

	lexer.eat("var ");

	std::string varName = lexer.readString();
	checkReserved(varName);

	if (!lexer.peek("=")) {
		lexer.eat(";");
		return new VarDeclNode(varName);
	}

	lexer.eat("=");

	auto valueExpr = exprParser.parseExpression();

	lexer.eat(";");
	
	return new VarDeclNode(varName, valueExpr);

}
