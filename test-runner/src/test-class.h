#pragma once

#include <string>

#include "../../src/Console.h"

#include "appveyor.h"

struct Test {

	TestData testData;

	virtual void init() = 0;

	virtual bool run() = 0;

	virtual void exec(int& countPass) final {

		init();

		testData.passed = run();
		countPass += testData.passed;

		Console::write("[ ");
		Console::write(testData.passed ? "PASS" : "FAIL", testData.passed ? Color::green : Color::red);
		Console::writeLn(" ] " + testData.description + " (file '" + testData.fileName + "')");

		AppVeyor::uploadTestResult(testData);

	}

};

template<class... Ts>
struct TestSuite : Ts... {

	int execute() {

		const std::size_t count = sizeof...(Ts);
		int countPass = 0;

		( Ts::exec(countPass), ...);

		Console::writeLn("\nExecuted " + std::to_string(count) + " tests, of which " + std::to_string(countPass) + " passed and " + std::to_string(count - countPass) + " failed.\n", 
								(count - countPass == 0) ? Color::green : Color::red);			

		return count - countPass;

	}

};