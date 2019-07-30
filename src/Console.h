/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Console.h
	@description:

*/
#pragma once

#include <iostream>

enum Color {
	white = 0, //TODO actually this is default color, I think?
	red = 31,
	yellow = 93,
	blue = 94
};

class Console {

public:

	inline static const std::string reset = "\033[0";

	static void write(const std::string& text, const Color color = Color::white){
		std::cout << "\033[0;" << color << "m" << text << reset;
	}

	static void writeLn(const std::string& text, const Color color = Color::white){
		write(text + "\n", color);
	}

	static void debug(const std::string& text){
		write("[DEBUG] ", Color::yellow);
		writeLn(text);
	}

};
