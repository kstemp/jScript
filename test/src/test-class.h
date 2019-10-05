#pragma once

#include <functional>
#include <sstream>
#include <string>

#include "controller.h"

#include "appveyor.h"
#include "assert.h"

#include "../../src/Console.h"

struct TestData {

	std::string testName;
	std::string fileName;
	bool passed;
	std::string duration;
	std::string errorMessage;
	std::string stackTrace;
	std::string stdOut;
	std::string stdErr;

};

namespace CppTest{

	std::function<TestData()> test(const std::string what, const std::function<void()> testCase){

		return [=]() -> TestData {

			TestData data;

			data.testName = what;
			data.passed = true;

			try {

				testCase();

			} catch (const AssertException& e) {

				data.passed = false;
				data.errorMessage = e.message();

			}

			Console::write("   ");

			if (data.passed)
				Console::writeInfoLn(what, "PASS", Color::green);
			else {
				Console::writeInfoLn(what, "FAIL", Color::red);

				Console::writeLn("          " + data.errorMessage);
			}

			return data;
		};

	}

template<class... Ts>
void describe(const std::string what, const Ts... lambdas){

	Controller::get().addTestSuite([=](){

		Console::writeLn("-> " + what);

		std::vector<TestData> data;

		( data.push_back(lambdas()), ...);

		size_t countPass = std::count_if(data.begin(), data.end(), [](auto&& dataElem) -> bool { return dataElem.passed; });
		/*
		if (Config::appVeyor){
			for (int i = 0; i < data.size(); ++i){
				data[i].testName = what + " -> " + data[i].testName;
				//AppVeyor::uploadTestResult(data[i]);
			}
		}*/

		Console::writeLn("\n   Executed " + std::to_string(data.size()) + " tests, of which " + std::to_string(countPass) + " passed and " + std::to_string(data.size() - countPass) + " failed.\n", 
									(data.size() - countPass == 0) ? Color::green : Color::red);			

	});

	}

}