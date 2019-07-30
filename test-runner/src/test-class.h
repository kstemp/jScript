#pragma once

#include <string>

struct Test {

	virtual std::string describe() = 0;;
	virtual void run() = 0;

	void exec(){
		std::cout << describe() << ": ";
		run();
		std::cout << " [PASS]\n";
	}

};

template<class... Ts>
struct TestRunner : Ts... {

	void execute() {
		(Ts::exec(), ...);
	}

};