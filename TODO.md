# TODO

* fix AppVeyor warnings (struct/class...)
* erros handling - including position of the error, distinction into ParserError/RuntimeError etc.
* lexical scoping

## Bugs 

* does not properly handle empty line at the end of input ("cannot parse expression"), may be related to some subtleties with checking for EOF
