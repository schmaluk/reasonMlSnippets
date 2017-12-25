/* Currying:
   - Funktion werden in Reason standardmäßig gecurried
     d.h.:
   */
let f = (x, y, z) => Js.log({j|x: $x y: $y z: $z|j});

f("hallo", "wie", "gehts");

/*
  wird zu:
 - let f = x => y => z => Js.log({j|x: $x y: $y z: $z|j});
 */
/*
 Anwendungsfälle für Currying:
 - Dependency Injection:
 */
/* Einfache Funktion mit named Parameters */
let greeter = (~greeting: string, ~persons: list(string)) =>
  List.map(name => {j|$greeting, $name|j}, persons);

/* Dependency Injection wird durch Currying möglich: */
let merryXmas = greeter(~greeting="Merry Christmas");

/* Funktion mit (pre-set) einem bereits gesetztem Argument
   und einem freien restlichen Parameter */
let xmasWishes = merryXmas(~persons=["Alex", "Sophie"]);

Js.log(xmasWishes);