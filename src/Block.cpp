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

	Node* expr = parseExpression();

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

	out->expr = parseExpression();

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

	Node* valueExpr = parseExpression();

	lexer.eat(";");
	
	return new VarDeclNode(varName, valueExpr);

}


/*

		Node* parseVariableOrFunction()

		@description: TODO

	*/
Node* Parser::parseVariableOrFunction() {

	std::string name;
	while (isalpha(lexer.current())) {
		name += lexer.current();
		lexer.advance();
	}

	lexer.skipSpacesTabsNewlines();

	if (!lexer.peek("("))
		return new VariableNode(name);

	lexer.eat("(");

	FuncCallNode* out = new FuncCallNode(name);

	while (!lexer.peek(")")) {
		lexer.skipSpacesTabsNewlines();
		out->arguments.push_back(parseExpression());
		if (!lexer.peek(")"))
			lexer.eat(",");
	}

	lexer.eat(")");

	return out;
}


/*

	Node* getNumber

	@description:	creates a new ValueNode which represents a number (int or double) found
					in the script
	@returns:		pointer to new ValueNode

*/
Node* Parser::parseValueNode() {

	std::string out;
	while (isdigit(lexer.current())) {
		out += lexer.current();
		lexer.advance();
	}

	// if there's no dot, we return an integer 
	if (lexer.current() != '.')
		return new ValueNode(std::stoi(out));

	lexer.advance();
	out += '.';

	while (isdigit(lexer.current())) {
		out += lexer.current();
		lexer.advance();
	}

	return new ValueNode(std::stod(out));

}
