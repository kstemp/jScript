#include "Operator.h"
#include "Lexer.h"
#include "Node.h"

#include <stack>	

struct ExpressionParser {

	Lexer& lexer;

	ExpressionParser(Lexer& lexer) : lexer(lexer) {}

	std::stack<OperatorValue> stack;

	OperatorType parseBinaryOperator() {

	/*	lexer.skipSpacesTabsNewlines();

		OperatorType returnVal = OperatorType::None;

		// TODO make a map with operators, and just do return operatorMap[lexer.current]
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
		*/
		return OperatorType::None;
	//	return new ValueNode(9);
	
	}



	Node* parseValue() {

	/*	lexer.skipSpacesTabsNewlines();

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

			auto cur = lexer.current();

			if (isalpha(lexer.current()))
				return  parseVariableOrFunction();

			throw Exception("failed to parse expression", lexer.pos());


		}*/
		return new ValueNode(9);
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


	/*

			Node* parseVariableOrFunction()

			@description: TODO

		*/
	Node* parseVariableOrFunction() {

	/*	std::string name;
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

		return out;*/
	}


	/*

		Node* getNumber

		@description:	creates a new ValueNode which represents a number (int or double) found
						in the script
		@returns:		pointer to new ValueNode

	*/
	Node* parseValueNode() {

		/*std::string out;
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

		return new ValueNode(std::stod(out));*/

	}


};
