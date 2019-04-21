/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		main.cpp
	@description:	

*/

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Console.h"
#include "Exception.h"
#include "Version.h"

#include "Interpreter.h"

/*

	int main(int argc, char *argv[])

	@description:	application entry point. 
					Collects arguments from command line, 
					reads the specified source, parses it and executes the script	

*/
int main(int argc, char* argv[]) {

	// no input files
	if (argc == 1) {

		consoleWriteLn("Error: no input file specified", Color::Red);
		return 1;

	}

	// load input to memory
	std::stringstream buffer;
	try {

		buffer << (std::ifstream(argv[1])).rdbuf();

	} catch (const std::ifstream::failure& e) {

		consoleWriteLn("Error: file '" + std::string(argv[1]) + "' cannot be opened (" + e.what() + ")");
		return 1;

	}

	std::string input = buffer.str();

	Interpreter interpreter(std::cout);

	try {
	
		interpreter.init(input);
	
	} catch (const Exception& e) {

		consoleWriteLn("Parser exception at position " + std::to_string(e.pos()) + ": " + std::string(e.what()), Color::Red);

		size_t pos1 = input.find_last_of('\n', e.pos());
		size_t pos2 = input.find_first_of('\n', e.pos());

		if (pos1 == std::string::npos)
			pos1 = 0;

		if (pos2 == std::string::npos)
			pos2 = input.length();

		consoleWriteLn(input.substr(pos1, pos2 - pos1));

		std::string p = "";
		for (size_t i = pos1; i < e.pos() - 1; i++)
			p += (input[i] == '\t' ? '\t' : ' ');

		consoleWriteLn(p + "^");

		return 1;

	}

	try {

		interpreter.run(true);
	
	} catch (const Exception& e) {

		consoleWriteLn("Error: " + std::string(e.what()), Color::Red);
		return 1;

	}

}

