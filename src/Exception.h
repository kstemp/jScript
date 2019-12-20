#pragma once

#include <string>
#include <exception>

enum class ExceptionType {
	undefinedArgToBinOp
};

constexpr auto getExceptionMessage(ExceptionType type) {
	switch (type) {
	case ExceptionType::undefinedArgToBinOp:
		return "undefined argument to binary operator";
	default: 
		return "what?";
	}
}

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

		Exception(ExceptionType type)
			: _message(getExceptionMessage(type)), _pos(-69) {}

		Exception(const std::string message, const size_t pos = -69)
			: _message(message), _pos(pos) {}

};