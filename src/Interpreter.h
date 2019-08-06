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

	std::ostream& _out;

	std::vector<Node*> program;

public:

	void reset() {

		// initialize global scope. It is the only scope that can contain function declarations
		scopes.clear();
		scopes.push_back(Scope("global"));
	
	}

	void resolveVariables() {

		reset();

		auto resolver = new Resolver;

		//TODO destructors!!!!!!!!!

		try {

			for (auto& it : program) 
				it->accept(resolver);

		}	catch (const Exception& e) {

			delete resolver;
			throw e;

		}

	}

	void run(const bool printNumericalResults = false){

		resolveVariables();

		reset();

		Visitor* visitor = new Visitor;

		//TODO destructors!!!!!!!!!

		try {
			
			for (auto& it : program) {

				it->accept(visitor);
				
				if (printNumericalResults)
					if (!visitor->result.isUndefined())
						_out << visitor->result;
				
			}

		} catch (const Exception&  e) {
			
			delete visitor;
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