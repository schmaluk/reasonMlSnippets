/*
 Lists: [ a, b, c, ... ]
 - immutable
 - konzipiert für sequentieller Zugriff aber nicht wahlfreiem Zugriff
 - container für Daten gleichen Typs, d.h. homogen
 - einfach verkettet
 */
let logList = list =>
  list |> Array.of_list |> Js.Array.joinWith(", ") |> Js.log;

/*
 *
 Literal-Schreibweise:
 - [a, b, c]
 */
let meineListe = ["a", "b", "c"];

logList(meineListe);

/*
 *
 Prepend-Operator via Destructuring-Operator ... in Reason:
 - [a, b, c, ...liste]
 */
let meineListe = ["anfang", ...meineListe];

logList(meineListe);

/*
 *
 Listen-Konkatenierung:
 - List.concat([liste1, liste2, ...])
 */
let meineWeitereListe = ["Ente", "gut", "alles", "gut"];

let listenConcatenated = List.concat([meineListe, meineWeitereListe]);

logList(listenConcatenated);

/**
 * Wahlfreier Zugriff bei Listen in-effizient in Reason via:
 * - List.nth(index, liste);
 *
 * Sequentieller Zugriff bei [a, b, c] effizient.
 * Listen-Zugriff über Destructuring.
 * Für wahlfreien Zugriff sind Arrays besser: [|a, b, c|]
 */
let head = List.hd(listenConcatenated);

Js.log(head);

let fuenfter = List.nth(listenConcatenated, 4);

Js.log({j|fünfter : $fuenfter|j});

/*
 * Listen-Länge:
 * List.length(liste)
 */
let length = List.length(listenConcatenated);

Js.log({j|length : $length|j});

if (List.length(listenConcatenated) > 4) {
  /*
   Destructuring the list via pattern matching:
   let [a, b, c, ...rest] = liste;
   */
  let [a, b, c, d, ...rest] = listenConcatenated;
  Js.log({j|a: $a, b: $b, c: $c, d: $d|j});
  logList(rest);
};

/*
 Arrays: [| a, b, c, ... |]
 - konzipiert für schnellen wahlfreien Zugriff mittels Index
 - homogener Datencontainer mit Elementen gleichen Typs
 - mutable
 - mapt 1:1 zu einem JS-Array, d.h. Js.Array.t('a)
 - feste Länge
 */
let meinArray: array(string) = [|"a", "b", "c", "d"|];

Js.log(meinArray);

/*
 *
  Wahlfreier Zugriff über Index:
  - array[index]
  */
Js.log(meinArray[2]);

/*
 *
 Länge eines Arrays:
 - Array.length(array)
 */
Js.log(Array.length(meinArray));

/*
  *
  Mutable via Zuweisung:
 - array[index] = newValue;
 */
meinArray[3] = "wurst";

Js.log(meinArray);

/*
  *
  Implzite Umwandlung eines Reason-Arrays array('a) <--> Js-Array Js.Array.t('a):
 - ein array('a) ist nur ein Alias für ein Js.Array.t('a)
 - kein Typecast notwendig für Reason-Arrays
  */
let logJsArray: Js.Array.t('a) => unit =
  input =>
    input |> Js.Array.joinWith(", ") |> (v => Js.log({j|logJsArray: $v|j}));

/* Impliziter Typ-Cast von: array(string) --> Js.Array.t(string) */
logJsArray(meinArray);

/* Impliziter Typ-Cast von: Js.Array.t(int) --> array(int) */
let nochnArray: array(int) = [%raw "[1,2,99,1000,-4]"];

let logReasonArray: array(int) => unit = logJsArray;

logReasonArray(nochnArray);