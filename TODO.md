# TODO

* reduce the amount of boilerplate code for arithmetic operations on variables - we have std::plus, then overload of +, then getVarr etc. 
* erros handling - including position of the error, distinction into ParserError/RuntimeError etc.
* lexical scoping
* fix AppVeyor warnings (struct/class...)
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

## Bugs 

* does not properly handle empty line at the end of input ("cannot parse expression"), may be related to some subtleties with checking for EOF
