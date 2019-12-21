#pragma once

#include <string>

#include "Exception.h"

class Lexer {

	std::istream& input;

	bool _eof() {
		input.peek();
		return input.eof();
	}

	void _skipSpaces() {
		while (isspace(input.peek()))
			input.ignore();
	}

	std::string _readInteger() {

		std::string out;
		while (isdigit(input.peek()))
			out += input.get();

		return out;

	}

	std::string _readStringName() {

		std::string out;
		while (isalnum(input.peek()))
			out += input.get();

		return out;

	}

	bool _isOperator(char c) {

		return (c == '{'
			|| c == '}'
			|| c == '+'
			|| c == '-'
			|| c == '*'
			|| c == '/'
			|| c == '('
			|| c == ')'
			|| c == ';'
			); // TODO add all

	}


public:

	Lexer(std::istream& input) : input(input) {}

	std::vector<std::string> tokenize() {

		// TODO spaces at the end of input STILL CAUSE AN ERROR!!!!
		std::vector<std::string> out;
		while (!_eof()) {

			_skipSpaces();

			char c = input.peek();

			if (isdigit(c)) {
				out.push_back(_readInteger());
			}
			else if (_isOperator(c))
			{
				out.push_back(std::string(1, input.get()));
			}
			else if (isalpha(c))
			{
				out.push_back(_readStringName());
			}
			else
			{
				throw Exception("Unexpected token!");
			}

		}

		return out;
	}

};
