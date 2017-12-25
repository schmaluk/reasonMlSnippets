/*
 Das Typ-System in OCaml:
 - Keine Nested Records möglich:
   https://stackoverflow.com/questions/43461007/ocaml-nested-structure
 - OCaml hat keine strukturelles Typ-System:
 https://en.wikipedia.org/wiki/Structural_type_system
 sondern ein nominales Typ-System:
 https://en.wikipedia.org/wiki/Nominal_type_system
 */
/*
 *
 Type-Declaration of a nested record
 */
type nestedJunk = {
  payload: string,
  junkLevel1
}
and junkLevel1 = {
  payload: string,
  junkLevel2
}
and junkLevel2 = {
  payload: string,
  junkLevel3
}
and junkLevel3 = {payload: string};

/* Object creation */
let junk: nestedJunk = {
  payload: "just on junkLevel0",
  junkLevel1: {
    payload: "1 stage down on junkLevel1",
    junkLevel2: {
      payload: "further down the stairs to junkLevel2",
      junkLevel3: {
        payload: "reached basement on junkLevel3"
      }
    }
  }
};

/* Destructuring of object */
let {
  payload: p0,
  junkLevel1: {
    payload: p1,
    junkLevel2: {payload: p2, junkLevel3: {payload: p3}}
  }
} = junk;

/* Logging destructured values: */
print_endline(
  {j|
payload p0: $p0
payload p1: $p1
payload p2: $p2
payload p3: $p3
    |j}
);