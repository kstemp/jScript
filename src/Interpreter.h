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

std::unordered_map<std::string, FunctionNode*> methods; 

class Interpreter {

	std::vector<Node*>& program;

public:

	Interpreter(std::vector<Node*>& program) : program(program) {}
	
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

	void run(){

		resolveVariables();

		reset();

		auto visitor = new RunVisitor;

		//TODO destructors!!!!!!!!!

		try {
			
			for (auto& it : program) {

				it->accept(visitor);

				if (!visitor->result.isUndefined())
					std::cout << visitor->result;
				
			}

		} catch (const Exception&  e) {
			
			delete visitor;
			throw e;

		}

	}

};