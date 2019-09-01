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

/*

	int main(int argc, char *argv[])

	@description:	application entry point. 
					Collects arguments from command line, 
					reads the specified source, parses it and executes the script	

*/
int main(const int argc, const char* argv[]) {

	// no input files
	if (argc == 1) {

		Console::writeError("no input file specified");
		return 1;

	}

	// load input to memory
	std::stringstream buffer;
	try {

		buffer << (std::ifstream(argv[1])).rdbuf();

	} catch (const std::ifstream::failure& e) {

		Console::writeError("file '" + std::string(argv[1]) + "' cannot be opened (" + e.what() + ")");
		return 1;

	}

	Interpreter interpreter(buffer, std::cout);

	try {
	
		interpreter.parse();
	
	} catch (const Exception& e) {

		Console::writeError("Parser exception at position " + std::to_string(e.pos()) + ": " + std::string(e.what()));

/*
		size_t pos1 = input.find_last_of('\n', e.pos());
		size_t pos2 = input.find_first_of('\n', e.pos());

		if (pos1 == std::string::npos)
			pos1 = 0;

		if (pos2 == std::string::npos)
			pos2 = input.length();

		Console::writeLn(input.substr(pos1, pos2 - pos1));

		std::string p = "";
		for (size_t i = pos1; i < e.pos() - 1; i++)
			p += (input[i] == '\t' ? '\t' : ' ');

		Console::writeLn(p + "^");
*/
		return 1;

	}

	try {

		interpreter.run(true);
	
	} catch (const Exception& e) {

		Console::writeError(std::string(e.what()));
		return 1;

	}

}

