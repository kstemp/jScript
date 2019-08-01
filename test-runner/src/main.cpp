
#include <iostream>

#include "assert.h"
#include "test-class.h"

const std::string SPLASH_MSG = "\njScript test-runner utility v.0.1\ncopyright (C) 2019 by K. Stempinski\n\n";

struct Test1 : Test {

	void init() override {
		testData.fileName = "variable/test.j";
		testData.description = "test description 1";
	}

	bool run() override {
		Assert_AreEqual(2+2, 4);
	}

};

struct Test2 : Test {

	bool run() override {
		Assert_IsTrue(2 == 2);
	}

	void init() override {
		testData.fileName = "func/test2.j";
		testData.description = "another test description";
	}

};

int main(int argc, char** argv){

	std::cout << SPLASH_MSG;

	return TestSuite<
		Test1,
		Test2
	>{}.execute();

}
