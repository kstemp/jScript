/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Console.h
	@description:

*/
#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

enum Color {

	Red		= FOREGROUND_RED,
	Blue	= FOREGROUND_BLUE,
	Green	= FOREGROUND_GREEN,
	White	= FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN,
	Yello	= FOREGROUND_RED | FOREGROUND_GREEN

};

void setTextColor(const Color color) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, color);

}

void consoleWriteLn(const std::string& text, const Color color = Color::White) {

	setTextColor(color);
	std::cout << text << "\n";
	setTextColor(Color::White);

}


