/*

	jsc
	copyright (C) 2019 K. Stempinski

	@filename:		main.cpp
	@description:	entry point of the script-runner utility

*/

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Console.h"
#include "Exception.h"
#include "Interpreter.h"

int main(const int argc, const char* argv[]) {

	while (1) {

		std::cout << "> ";

		std::string input;
		std::getline(std::cin, input);

		std::stringstream buffer(input);

		std::vector<Node*> program;

		try {

			Lexer lexer(buffer);

			auto tokens = lexer.tokenize();

			for (auto& t : tokens)
				std::cout << t << "\n";

			Parser parser(tokens);
			program = parser.parse();

		}
		catch (const Exception & e) {

			Console::writeError("Parser exception at position " + std::to_string(e.pos()) + ": " + std::string(e.what()));
			return 1;

		}

		try {

			Interpreter interpreter(program);
			interpreter.run();

		}
		catch (const Exception & e) {

			Console::writeError(std::string(e.what()));
			return 1;

		}

	}

}

