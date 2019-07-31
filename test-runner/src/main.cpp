
#include <iostream>

#include "test-class.h"

#include <chrono>
#include <thread>

const std::string SPLASH_MSG = "\njScript test-runner utility v.0.1\ncopyright (C) 2019 by K. Stempinski\n\n";
const std::string CMD_LINE_ARGS_MSG = "Command line arguments: test-runner [fileName.xml]\n\n"; 

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
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		return true;
	}

	void initialize() override {

	}

};

int main(int argc, char** argv){

	std::cout << SPLASH_MSG;

	if (argc == 1)
		std::cout << CMD_LINE_ARGS_MSG;

	TestRunner<
		Test1,
		Test2
	>{}.execute();

}
