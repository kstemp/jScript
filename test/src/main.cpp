
#include <iostream>

#include "cpptest.h"

#include "../tests/Variable.h"


int main(const int argc, const char** argv){

	testVariable();

	CppTest::Controller::get().runAllTestSuites();
}
