# TODO

## Bugs 

* does not properly handle empty line at the end of input ("cannot parse expression")
* if a node does not return a value, it should at least erase the previous value - note that code 

~~~~ 
2+2*2;  
(2+2)*2;  
  
func test(){ 
    
}

test();
~~~~

produces output 

~~~~ 
[int] 6  
[int] 8  
[int] 8  
[int] 8
~~~~

## Critical

* erros handling - including position of the error, distinction into ParserError/RuntimeError etc.

## Features

* ```if``` statements
* ```for``` loops
* ```Char``` data type
* pointers
* a simple REPL or something similar,
