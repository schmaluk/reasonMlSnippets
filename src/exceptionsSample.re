/* Exceptions */
/*
 Links:
 - https://reasonml.github.io/guide/language/exception
  */
/*
 Exception-Declaration:
    - syntax: exception Constructor(type1, type2, ...)
    - Must be capitalized as Constructors used in Variants
    */
exception NoConnection(int, string);

/*
  Raise Exceptions:
     - raise-syntax: raise(MeineException(...));
 */
let f = input => {
  if (input == "fehler") {
    raise(NoConnection(500, "Keine Ahnung was da kaputt ist"));
  };
  "Nochmal gut gegangen";
};

/* Catch Exception:
Due to the absence of statements in Reason:
You catch exception in reason by returning a default value,
if the exception is matched in an expression.

- try-syntax: 
let value = try(functionCall()) {
    | MeineException1(...) => defaultValue1;
    | MeineException2(...) => defaultValue2;
    ...
}
- normal pattern-matching with switch:
let value = switch(functionCall()) {
    | Value1(x, y) => ...
    | MeineException(...) => defaultValue;
}
*/
try()

switch(f("fehler")){
 | 
}