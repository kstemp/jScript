/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Interpreter.h
	@description:

*/
#pragma once

#include <deque>
#include <unordered_map>
#include <vector>

#include "Node.h"
#include "Lexer.h"
#include "Parser.h"
#include "Scope.h"

std::deque<Scope> scopes;

std::unordered_map<std::string, FunctionNode*> methods; 

class Interpreter {

private:

	std::ostream& _out;

	std::vector<Node*> program;

public:

	void reset() {

		// initialize global scope. It is the only scope that can contain function declarations
		scopes.clear();
		scopes.push_back(Scope("global"));
	
	}

	void run(const bool printNumericalResults = false){

		reset();

		Visitor* visitor = new Visitor;

			//TODO destructor

		try {
			
			for (auto& it : program) {

				it->accept(visitor);
				
				//Variable result = it->visit();
				
				if (printNumericalResults)
					if (visitor->result.type() != VarType::Undefined)
						_out << visitor->result << "\n";
				
			}

		} catch (const Exception&  e) {
			
			throw e;

		}

	}

	void init(const std::string& input) {

		// cleanup
		for (auto& it : program)
			delete it;

		program.clear();

		Lexer lexer(input);
		Parser parser(lexer);

		try {

			parser.parse(program);

		} catch (const Exception& e) {

			throw e;

		}
	
	}

	Interpreter(std::ostream& out) : _out(out) {}

};