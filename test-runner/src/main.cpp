
#include <iostream>

#include "test-class.h"

#include <chrono>
#include <thread>

const std::string SPLASH_MSG = "\njScript test-runner utility v.0.1\ncopyright (C) 2019 by K. Stempinski\n\n";
const std::string CMD_LINE_ARGS_MSG = "Command line arguments: test-runner [fileName.xml]\n\n"; 

#include "assert.h"

struct Test1 : Test {

	void init() override {
		scriptFile = "variable/test.j";
	}

	std::string describe() override {
		return "is true";
	}

	bool run() override {
		Assert_AreEqual(2+2, 4);
		//Assert_AreEqual(5, 5);
	}

};

struct Test2 : Test {

	std::string describe() override {
		return "another test";
	}

	bool run() override {
		Assert_IsTrue(false);
	}

	void init() override {

	}

};

int main(int argc, char** argv){

	std::cout << SPLASH_MSG;

	if (argc == 1)
		std::cout << CMD_LINE_ARGS_MSG;

	TestSuite<
		Test1,
		Test2
	>{}.execute();

}
