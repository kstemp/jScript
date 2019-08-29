#pragma once

#include <string>

#include "Exception.h"

class Lexer {

	std::istream& input;

//	size_t pos;

//	size_t lineNumber;

public:

	[[nodiscard]] size_t gpos() const{
		return input.tellg();
	}

	[[nodiscard]] bool eof() const {
		//return pos >= input.size();
		return (input.peek() == EOF);
	}

	void advance(){
		input.seekg(1, std::ios_base::cur);
	}

	[[nodiscard]] char current() const{
		return input.peek();
		//return input[pos];
	}

	Lexer(std::istream& input) : input(input) {}

	/*
	
		void skipWhitespaces()
	
		@description:	^^
	
	*/
	void skipSpacesTabsNewlines(const bool skipNewlines = true){

		while (isspace(input.peek()) || (skipNewlines && input.peek() == '\n') || input.peek() == '\t')
			input.ignore();
		//while (isspace(input[pos]) || input[pos] == '\n' || input[pos] == '\t')	{
		//	pos++;
		//};

	}

	/*

		std::string readString()

		@description:	^^

	*/
	[[nodiscard]] std::string readString(){

		std::string out;
		while (isalnum(input.peek()))//{
			out += input.get();
		//	pos++;
		//}
		return out;

	}

	//TODO merge these two into one
	//TODO exceptions
	void eat(const std::string& keyword){

		//const std::streampos pos = input.tellg();

		skipSpacesTabsNewlines(false);

/*		std::string read;

if (input >> read){

	if (read != keyword){

	}

} else 
{

}
*/
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

/*
		const size_t foundPos = input.find_first_not_of(" \t\n", pos);

		//TODO comment
		if (foundPos == std::string::npos)
			throw Exception("EOF!", pos);

		// can't fit
		if (foundPos + keyword.length() > input.length())
			throw Exception("to little space!", pos);

		const std::string sub = input.substr(foundPos, keyword.length());

		if (sub == keyword)
			pos = foundPos + keyword.length();
		else
			throw Exception("expected '" + keyword + "'", pos);
*/
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
//				throw Exception("expected '" + keyword + "'", pos); 
		}
	input.seekg(_pos_, std::ios_base::beg);
std::cout << "peeked " << keyword << "\n"; 
		return true;

/*
		size_t foundPos = input.find_first_not_of(" \t\n", pos);

		//TODO comment
		if (foundPos == std::string::npos)
			return false;

		// can't fit
		if (foundPos + keyword.length() > input.length())
			return false;

		return input.substr(foundPos, keyword.length()) == keyword;*/

	}

};
