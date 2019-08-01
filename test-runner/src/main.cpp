
#include <iostream>

#include "assert.h"
#include "test-class.h"

const std::string SPLASH_MSG = "\njScript test-runner utility v.0.1\ncopyright (C) 2019 by K. Stempinski\n\n";
const std::string CMD_LINE_ARGS_MSG = "Command line arguments: test-runner [fileName.xml]\n\n"; 



struct Test1 : Test {

	void init() override {
		scriptFile = "variable/test.j";
	}

	std::string describe() override {
		return "is true";
	}

	bool run() override {
		Assert_AreEqual(2+3, 4);
	}

};

struct Test2 : Test {

	std::string describe() override {
		return "another test";
	}

	bool run() override {
		Assert_IsTrue(2 == 2);
	}

	void init() override {

	}

};

int main(int argc, char** argv){

	std::cout << SPLASH_MSG;

	if (argc == 1)
		std::cout << CMD_LINE_ARGS_MSG;

	return TestSuite<
		Test1,
		Test2
	>{}.execute();

}
