# CppTest

[![Build status](https://ci.appveyor.com/api/projects/status/4xad36dqkd5xbf17?svg=true)](https://ci.appveyor.com/project/kstemp/cpptest)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A small, easy-to-use unit testing framework for C++, inspired by <img width = 16 height = 16 src="https://jestjs.io/img/favicon/favicon.ico"/>[Jest](https://jestjs.io/) testing framework for JavaScript. 

## Features

* **Integration with <img width = 14 height = 14 src = "https://www.appveyor.com/assets/img/favicons/favicon-32x32.png" />[AppVeyor](appveyor.com)** - CppTest can automatically upload test results via the BuildWorker API. 

## Example

~~~~
#include "CppTest.h"

template<typename... T>
auto add(T... args){
	return ( args + ...);
}

int main(const int argc, const char** argv){

  describe("The addNumbers function", 

    test("Should work for valid input", [](){
    
      Assert::AreEqual(add(1, 3, 6, 8), 1 + 3 + 6 + 8);
      
    })

  );
  
  describe("Test Suite with exception catching example", 

    test("Should catch exception", [](){
    
      Assert::Throws<std::exception>([](){
      	throw std::exception("Hello there!");
      });
      
    })

  );  
  
  Controller::get().runAllTestSuites();

}
~~~~

## Supported Assertions: 
* `Assert::AreEqual(const T& actual, const T& expected)`,
* `Assert::AreNotEqual(const T& actual, const T& expected)`,
* `Assert::IsTrue(const T& actual)`,
* `Assert::IsFalse(const T& actual)`,
* `Assert::IsNull(const T& actual)`,
* `Assert::IsNotNull(const T& actual)`,
* `Assert::Throws<T>(const std::function<void()>&)`.
