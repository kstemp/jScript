/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Console.h
	@description:

*/
#pragma once

#include <iostream>
#include <map>

#include "Config.h"

const std::string reset = "\033[0m";
const std::string open = "\033[";

enum Color {
	white = 0,
	red = 1,
	green = 2,
	yellow = 3,
	blue = 4
};

const std::array<std::string, 5> colorStrings = {"", open + "31m", open + "92m", open + "93m", open + "94m"};

class Console {

public:

	static void write(const std::string& text, const Color color = Color::white){
#ifdef NO_CONSOLE_COLORS
		std::cout << text;
#else
		std::cout << colorStrings[color] << text << reset;
#endif
	}

	static void writeLn(const std::string& text, const Color color = Color::white){
		write(text + "\n", color);
	}

	static void lineUp(){
		std::cout << "\033[F";
	}

	static void lineStart(){
		std::cout << "\r";
	}

	static void writeInfoLn(const std::string text, const std::string& infoText, Color infoTextColor = Color::white){
		write("[ ");
		write(infoText, infoTextColor);
		write(" ] " + text + "\n");
	}
};
