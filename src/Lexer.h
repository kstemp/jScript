#pragma once

#include <string>

#include "Exception.h"

class Lexer {

private:

	const std::string input;

	size_t pos;

public:

	const size_t gpos() const {
		return pos;
	}

	bool eof() {
		return pos >= input.size();
	}

	void advance() {
		pos++;
	}

	const char current() const {
		return input[pos];
	}

	Lexer(const std::string& input) : input(input), pos(0) {}
	
	/*
	
		void skipWhitespaces()
	
		@description:	^^
	
	*/
	void skipSpacesTabsNewlines() {
	
		while (isspace(input[pos]) || input[pos] == '\n' || input[pos] == '\t')
			pos++;
	
	}

	/*

		std::string readString()

		@description:	^^

	*/
	const std::string readString() {

		std::string out;
		while (isalnum(input[pos])) {
			out += input[pos];
			pos++;
		}
		return out;

	}

	//TODO exceptions
	void eat(const std::string& keyword) {
	
		size_t foundPos = input.find_first_not_of(" \t\n", pos);

		//TODO comment
		if (foundPos == std::string::npos)
			throw Exception("EOF!", pos);

		// can't fit
		if (foundPos + keyword.length() > input.length())
			throw Exception("to little space!", pos);

		std::string sub = input.substr(foundPos, keyword.length());

		if (sub == keyword) 
			pos = foundPos + keyword.length();
		else 
			throw Exception("expected '" + keyword + "'", pos);

	
	}

	const bool peek(const std::string& keyword) const {

		size_t foundPos = input.find_first_not_of(" \t\n", pos);

		//TODO comment
		if (foundPos == std::string::npos) 
			return false;

		// can't fit
		if (foundPos + keyword.length() > input.length())
			return false;
		
		return input.substr(foundPos, keyword.length()) == keyword;

	}

};