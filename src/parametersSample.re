/* Links: https://reasonml.github.io/guide/language/function */
/* Standard Positional Arguments */
let test1 = a => Js.log({j|test1: $a|j});

test1(22);

let test2 = (a, b) => Js.log({j|test2: $a, $b|j});

test2(1, 2);

/* Labeled Arguments */
let test3 = (a, b, ~c) => Js.log({j|test3: $a, $b, $c|j});

test3(1, 2, 3);

test3(~c=3, 1, 2);

test3(1, ~c=3, 2);

/* Labeled Parameters können optional gemacht werden:
   ~a=?
   Der optionale Parameter sollte vor einem positionalem
   Parameter stehen, um Verwirrung beim Currying zu vermeiden.
   */
/* !! Optionale Parameter sind vom Typ: option('a)
    D.h. das übergebene Argument wird in einem option('a)
    gewrapped, ist aber selbst nicht vom Typ option('a)
   */
let test4 = (a, b, ~c: option(string)=?) =>
  /* Not good: Optional parameter at the end of the parameter-list */
  switch c {
  | None => Js.log({j|test4: $a, $b|j})
  | Some(value) => Js.log({j|test4: $a, $b, $value|j})
  };

/* Problem ist jetzt hier: Currying
   Dies ist eine Funktion, statt des Aufrufs selbst:
   */
test4(1, 2); /*  <-- Ist kein eigentlicher Fktns-Aufruf sondern Currying */

(test4(1, 2))(~c="optionaler Parameter");

/*
 Besser: Optionaler (Labeled) Parameter vor einem
 Positionalem (Ungelabeltem) Parameter
 */
let test5 = (a, ~b: option(string)=?, c) =>
  /* b ist jetzt hier vom Typ: option('a) */
  /* Beim Aufruf wird der rohe Wert im optionalem Parameter
     übergeben, und im Funktionsaufruf dann in ein option('a)
     eingepackt:
     */
  switch b {
  /* denn Optionale Parameter sind vom Typ: option('a) */
  | None => Js.log({j|test5: a: $a, c: $c|j})
  | Some(value) => Js.log({j|test5: a: $a, b: $value, c: $c|j})
  };

/* b ist im Funktionsrumpf: None */
test5(1, 3);

/* Anhand des darauffolgenden Positionalem Parameter vor
   dem Optionalem (Labeled) Parameter erkennt Reason den
   eigentlichen Fktns-Aufruf */
test5(~b="wurst schmeckt", 1, 3); /* Das Argument wird eingepackt in ein option(string) */

/*
  *
  !! Regel: Merke Optionale (Labeled) Parameter niemals am Ende
         der Parameterliste anordnen wg. Currying
 *
 */
/*
 Übergabe eines options('a)-Value an den Optionalen Parameter beim Fktns.Aufruf:
 f(~x=?option)

 let f = (~x=?) => { ... (x ist vom Typ options('a) im Rumpf) };
 let nullableValue = Some wert;
 f(~x=?nullableValue)
 beim Funktionsaufruf verwenden mittels:
 ?optionsArg beim Funktions-Aufruf mit optionsArg vom Typ option('a)

 */
let nullable = Some("Ich existiere");

test5(1, 3, ~b=?nullable); /* arg ist vom Typ: option(string) statt string */

let nullable = None;

test5(1, 3, ~b=?nullable);

/*
 f(~x=?arg);
 optionsArg ist hier vom Typ: option(string) statt string
 und wird hier per ?optionsArg beim Funktionsaufruf in den
 Funktionsrumpf durchgereicht
 (ohne nochmals in ein option('a) gewrappt werden zu müssen)
 */
/*
 *
 Parameter mit Default-Value: Labeled Parameter
 */
let times = (n, f) => {
  let rec aux = (acc, f) =>
    if (acc > 0) {
      f();
      aux(acc - 1, f);
    };
  aux(n, f);
};

let test6 = (~spruch: string="Oben ist oben", repCount: int) =>
  /* Da das Argument dann immer vorhanden sein wird durch den Fallback zum default-Wert,
     wird hier der optionale Parameter auch nicht options('a) eingepackt
        */
  times(repCount, () => print_endline(spruch));

test6(10);

test6(~spruch="Atmen ist gesund", 2);

/*
 *
 Syntactic Sugar für Funktions-Aufrufe
 */
type katze = {
  name: string,
  alter: int,
  specialAttack: unit => string
};

let feller = {name: "Max", alter: 3, specialAttack: () => "kratzen"};

let pfoter = {name: "Moritz", alter: 2, specialAttack: () => "miauen"};

let mapToFeller = (~feller: katze, ~pfoter: katze) : string => feller.name;

/* Falls Label == Variable-Name, Funktions-Aufruf ohne explizite Zuweisung des Labeled Parameter */
mapToFeller(~pfoter, ~feller) |> print_endline;

/*
  *
   Funktions-Überladung ist nicht möglich in Reason:
   Funktions-Überladung: der derselbe Funktions-Name mit anderer Signatur (Parameterliste)

   Stattdessen gibts nur: Funktions-Überschreibung aka Shadowing
 */
let f = (x: string) => print_endline(x);

f("elf");

let f = (x: int) => x + 1 |> (value => Js.log({j| x + 1 : $value|j}));

/* f("elf"); --> Fehler, da f geshadowed wird */
f(11);