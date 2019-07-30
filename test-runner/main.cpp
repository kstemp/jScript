
#include <iostream>

#include "./src/test-class.h"

struct Test1 : Test {

	std::string describe() override {
		return "provides test1";
	}

	static const int test = 1;
	void run() override {
		std::cout << "running " << test;
	}

};

struct Test2 : Test {

	std::string describe() override {
		return "provides test 222222";
	}

	static const int test = 2;
	void run() override {
		std::cout << "running " << test;
	}

};

int main(){

	TestRunner<
		Test1,
		Test2
	>{}.execute();
	
	getchar();

}