#pragma once

#include <string>

#include "../../src/Console.h"

struct Test {

	virtual std::string describe() = 0;
	virtual bool run() = 0;
	virtual void initialize() = 0;

	void exec(int& countPass){

		initialize();

		Console::writeLn("[      ] " + describe());

		const bool pass = run();
		countPass += pass;

		Console::lineUp();
		Console::lineStart();
		Console::write("[ ");
		Console::writeLn(pass ? "PASS" : "FAIL", pass ? Color::green : Color::red);

	}

};

template<class... Ts>
struct TestSuite : Ts... {

	void execute() {

		static const std::size_t count = sizeof...(Ts);
		int countPass = 0;

		( Ts::exec(countPass), ...);

		Console::writeLn("\nExecuted " + std::to_string(count) + " tests, of which " + std::to_string(countPass) + " passed and " + std::to_string(count - countPass) + " failed.\n", 
								(count - countPass == 0) ? Color::green : Color::red);			

	}

};