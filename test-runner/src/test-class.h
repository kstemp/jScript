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
		Console::lineUp();

		const bool pass = run();
		countPass += pass;

		Console::lineStart();
		Console::write("[ ");
		Console::writeLn(pass ? "PASS" : "FAIL", pass ? Color::green : Color::red);

	}

};

template<class... Ts>
struct TestRunner : Ts... {

	void execute() {

		static const std::size_t count = sizeof...(Ts);
		int countPass = 0;

		( Ts::exec(countPass), ...);

		std::cout << "\nExecuted " << count << " tests, of which " << countPass << " passed and " << count - countPass << " failed.\n\n";
	}

};