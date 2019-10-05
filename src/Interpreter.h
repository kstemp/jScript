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
#include "Resolver.h"
#include "RunVisitor.h"

std::deque<Scope> scopes;

using Program = std::vector<Node*>;

std::unordered_map<std::string, FunctionNode*> methods; 

class Interpreter {

	std::istream& _in;
	std::ostream& _out;


public:

	Program program;
	
	void reset() {

		// initialize global scope. It is the only scope that can contain function declarations
		scopes.clear();
		scopes.push_back(Scope("global"));
	
	}

	void resolveVariables() {

		reset();

		auto resolver = new Resolver();

		try {

			for (auto& it : program) 
				it->accept(resolver);

		}catch (const Exception& e) {

			throw e;

		}

	}

	void run(const bool printNumericalResults = false){

		resolveVariables();

		reset();

		auto visitor = new RunVisitor;

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

	void parse() {

		// cleanup
		for (auto& it : program)
			delete it;

		program.clear();

		Lexer lexer(_in);
		Parser parser(lexer);

		try {

			parser.parse(program);

		} catch (const Exception& e) {

			throw e;

		}
	
	}

	Interpreter(std::istream& in, std::ostream& out) : _in(in), _out(out) {}

};