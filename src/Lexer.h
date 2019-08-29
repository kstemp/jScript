#pragma once

#include <string>

#include "Exception.h"

class Lexer {

	std::istream& input;

public:

	Lexer(std::istream& input) : input(input) {}

	[[nodiscard]] std::streampos pos() const {
		return input.tellg();
	}

	[[nodiscard]] bool eof() const {
		return input.peek() == EOF;
	}

	void advance() {
		input.seekg(1, std::ios_base::cur);
	}

	[[nodiscard]] char current() const {
		return input.peek();
	}

	void skipSpacesTabsNewlines(const bool skipNewlines = true) {

		while (isspace(input.peek()) || (skipNewlines && input.peek() == '\n') || input.peek() == '\t')
			input.ignore();

	}

	[[nodiscard]] std::string readString() {

		std::string out;
		while (isalnum(input.peek()))
			out += input.get();
	
		return out;

	}

	//TODO merge these two into one
	//TODO exceptions
	void eat(const std::string& keyword){

		skipSpacesTabsNewlines(false);

		for (const char& c : keyword){
		
			
				char p;
				input.get(p); 	
				if (input.eof())
					throw Exception("EOF!"); 
			
				if (p != c){
				std::cout << p << " while expected " << c << "\n";
				throw Exception("expected '" + keyword, 0); 
			
			}
		}

	}

	[[nodiscard]] bool peek(const std::string& keyword){


		const std::streampos _pos_ = input.tellg();

		skipSpacesTabsNewlines(false);

char k;
		for (const char& c : keyword){
			if (input.eof())
				{
					input.seekg(_pos_, std::ios_base::beg);
					return false;
				} 
			else {
				input.get(k);
				if (k != c){
	input.seekg(_pos_, std::ios_base::beg);
					return false;

			}
			}
		}
	input.seekg(_pos_, std::ios_base::beg);

		return true;


	}

};
