#pragma once

#include "../../src/Console.h"

#include <string>

struct Test {

	virtual std::string describe() = 0;
	virtual bool run() = 0;
	virtual void initialize() = 0;

	void exec(int& countPass){

		initialize();

		std::cout << "[      ] " << describe() << "\n";
		std::cout << "\033[F";

		bool pass;
		pass = run();

		//TODO refactor

		countPass += pass;
		const std::string msg = pass ? "PASS" : "FAIL";
		const int color = pass ? Color::green : Color::red;

		std::cout << '\r' << "[ " << "\033[0;" << color << "m" << msg << "\033[0;" << Color::white << "m\n";

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