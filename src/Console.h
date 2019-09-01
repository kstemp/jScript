/*

	jsc scripting language
	copyright (C) 2019 K. Stempinski

	Console.h

	<summary>
	Mostly a wrapper for printing coloured output, and pretty things
	like "[ TEXT ] some message goes here" etc.
	</summary>

*/
#pragma once

#include <iostream>
#include <array>
#include <functional>

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

const std::array<std::string, 5> colorStrings = { "", open + "31m", open + "92m", open + "93m", open + "94m"};

struct Console final {

	static void write(const std::string& text, const Color color = Color::white){
		std::cout << colorStrings[color] << text << reset;
	}

	static void writeLn(const std::string& text, const Color color = Color::white){
		write(text + "\n", color);
	}

	static void writeInfoLn(const std::string text, const std::string& infoText, const Color infoTextColor = Color::blue, const Color textColor = Color::white){
		write("[ ");
		write(infoText, infoTextColor);
		write(" ] ");
		writeLn(text, textColor);
	}

	static void writeDebug(const std::string text) {
		if constexpr (Config::debug)
			writeInfoLn(text, "DEBUG", Color::yellow);
	}

	static void writeError(const std::string text) {
		writeInfoLn(text, "ERROR", Color::red, Color::red);
	}

};
