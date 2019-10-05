#pragma once

#include <exception>
#include <string>
#include <sstream>
#include <functional>

// TODO generic method for reporting assertion errors - AreEqual, IsTrue etc. should ONLY perform the check, like val1 != val2 etc.

class AssertException : std::exception {

	const std::string _message;

public:

	AssertException(const std::string& message) : _message(std::move(message)) {}

	std::string message() const {
		return _message;
	}

};

struct Assert final {

	template<typename T, typename G>
	static void AreEqual(const T& actual, const G& expected) {

		// TODO refactor, pretty-printing SHOULD NOT HAPPEN HERE!
		_Assert(static_cast<bool>(actual == expected), "expected \033[91m" + std::to_string(actual) + "\033[0m to equal \033[92m" + std::to_string(expected) + "\033[0m");

	}

	template<typename T>
	static void AreNotEqual(const T& actual, const T& expected) {

		// TODO refactor, pretty-printing SHOULD NOT HAPPEN HERE!
		_Assert(static_cast<bool>(actual != expected), "expected \033[91m" + std::to_string(actual) + "\033[0m to NOT equal \033[92m" + std::to_string(expected) + "\033[0m");

	}

	template<typename T>
	static void IsTrue(const T& actual) {

		_Assert(static_cast<bool>(actual), "expected \033[91mfalse\033[0m to be \033[92mtrue\033[0m");		

	}

	template<typename T>
	static void IsFalse(const T& actual) {

		_Assert(static_cast<bool>(!actual), "expected \033[91mtrue\033[0m to be \033[92mfalse\033[0m");

	}

	template<typename T>
	static void IsNull(const T& actual) {

		_Assert(static_cast<bool>(actual == nullptr), "expected value to be NULL");

	}

	template<typename T>
	static void IsNotNull(const T& actual) {

		_Assert(static_cast<bool>(actual != nullptr), "expected value to NOT be NULL");

	}

	template<class T>
	static void Throws(const std::function<void()>& func) {

		enum Status {
			caughtCorrect,
			caughtDifferent,
			didNotCatch
		};

		Status status = Status::didNotCatch;

		try {

			func();

		} catch (const T& e) {
			status = Status::caughtCorrect;
		} catch (...) {
			status = Status::caughtDifferent;
		}

		_Assert(status == Status::caughtCorrect, status == Status::caughtDifferent ? "expression of some other type was caught" : "expected exception to be thrown");

	}

private:

	static void _Assert(const bool result, const std::string& message){

		if (!result){

			throw AssertException(message);

		}

	}

};