#pragma once

#include <string>
#include <exception>

class Exception : public std::exception {

	protected:

		const size_t _pos;

		const std::string _message;

	public:

		const size_t pos() const {
			return _pos;
		}

		const char* what() const noexcept { 
			return _message.c_str();
		}

		Exception(const std::string message, const size_t pos = -69)
			: _message(message), _pos(pos) {}

};