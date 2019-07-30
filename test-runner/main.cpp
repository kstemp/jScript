
#include <iostream>

#include "./src/test-class.h"

struct Test1 : Test {

	std::string describe() override {
		return "invalid grouping leads in a non-assignable node";
	}

	bool run() override {
		return true;
	}

	void initialize() override{
		
	}

};

struct Test2 : Test {

	std::string describe() override {
		return "another test";
	}

	bool run() override {
		return true;
	}

	void initialize() override {

	}

};

int main(){

	TestRunner<
		Test1,
		Test2
	>{}.execute();
	
	getchar();

}