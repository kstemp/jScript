/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Console.h
	@description:

*/
#pragma once

#include <iostream>

// this is the easiest way to emulate Color::red, as if we had an enum
// TODO find something better
namespace Colors {
	const std::string red = "\033[0;31m";
	const std::string yellow = "\033[0;93m";
	const std::string blue = "\033[0;94m";
	const std::string reset = "\033[0m"; // color...?
}

class Console {

public:

	static void write(const std::string& text, const std::string& color = ""){
		std::cout << color << text << Colors::reset;
	}

	static void writeLn(const std::string& text, const std::string& color = ""){
		write(text + "\n", color);
	}

	static void debug(const std::string& text, const std::string& color = ""){
		write("[DEBUG] ", Colors::yellow);
		writeLn(text);
	}

};
