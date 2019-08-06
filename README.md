[![Build status](https://ci.appveyor.com/api/projects/status/4kisqm39kkn4op3m?svg=true)](https://ci.appveyor.com/project/kstemp/jscript) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# jsc scripting language specification

## Data Types

jsc supports the following data types:

* ```Int```
* ```Double``` 
* ```Char```

plus the ```Undefined``` type (which is returned by functions by default). Type promotion rules are simple - if any term in an expression is ```Double```, everything else is casted to ```Double```.  However, if any variable in a given expression is ```Undefined```, an error is thrown.

Variable declaration is done as follows:
~~~~
var foo
~~~~

Optionally, a variable may be declared and initialized to a value:
~~~~
var foo = 69.420;	// foo is Double
var bar = 3728; 	// bar is Int
var rab = 'r'; 		// rab is Char
var baz;			// baz is Undefined
~~~~

jsc is dynamically typed, but all variables must be declared before they may be used. 

## Control Flow

### ```while``` loop

Example (calculating factorial of a number):
~~~~

var n = 5;
var ans = 1;

while (n > 1){

	ans = n * ans;
	n = n - 1;

}
~~~~

```ans``` is expectedly ```[int] 120``` when the script terminates.


## Functions

* Function declarations are permitted only in top-level ("global") scope,
* There are no forward declarations - the body of a function must be specified in the source file before the function can be called,
* Function names may be composed of alphanumeric characters, but cannot start with a digit.

**Syntax:** 
~~~~
func FuncName(param1, param2, param3){


}
~~~~

An optional return statement has the form ```return [expr];```. If there is no return statement, a function returns ```Undefined```. 

**Example** (summing two numbers passed as parameters):
~~~~
func sum(a, b){

	return a + b;

}

sum(5, 7);
~~~~

**Output:**
~~~~
[int] 12
~~~~

**Example** (computing n-th Fibonacci number):
~~~~
func fib(n){

	if (n < 2){
	
		return n;
	
	}

	return fib(n - 1) + fib(n - 2);

}

fib(7);
~~~~

**Output**:
~~~~
[int] 21
~~~~
