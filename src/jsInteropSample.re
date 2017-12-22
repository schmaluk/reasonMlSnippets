/* Javascript-Imports into Reason are done via Bucklescript  */
/* Module for those Imports have Js-Prefix */
/* https://bucklescript.github.io/docs/en/interop-cheatsheet.html */
/* *
 * */
/* Raw JS */
/* (1) Expression:  [%raw "..."]  */
let result: int = [%raw "3 + 4"];

Js.log(result);

let add: (int, int) => int = [%raw "(x, y)=> x+ y"];

Js.log(add(3, 99));

/* *
 * */
/* (2) Statement: [%%raw "..."] */
[%%raw "const minus = (x,y) => x-y"];

[@bs.val] external minus : (int, int) => int = "minus";

Js.log(minus(100, 1));

/* *
 * */
/* (3) Referenzieren von JS-Variablen in Reason: */
/* [@bs.val] external varInReason : type = "varInJs" */
[%%raw "const testVar = 444"];

[@bs.val] external test : int = "testVar";

Js.log(test);

/* *
 * */
/* (4) Den vernesteten Namespace eines importierten Modules verkürzen: */
/* [@bs.scope "..."] */
/* [@bs.val] [@bs.scope "./js/testModule"] */
/* external  */
/* *
 * */
/* Common DataTypes in JS & Reason: */
let f: float = 0.0;

let s: string = "s";

let a: array(string) = [|"a", "b"|];

/* *
 * */
/* Converted DataTypes: Reason --> JS */
let t: (string, int, string) = ("adada", 33, "zz");

/* *
 * */
/* Not-shared Datatypes between Reason <--> JS */
/* !!!!!! Not-Convertibles: */
/* !!!!!! Records, Variants, option, list: */
type recType = {
  name: string,
  value: int
};

/* Use Converters & Accessors: options, record */
/* *
 * */
/* Aufruf einer Methode auf einem Objekt */
/* [@bs.send]; */
type auto;

[@bs.module] [@bs.new]
external createAuto : string => auto = "../../../src/js/auto";

/* Eine Js-Methode auf einem Js-Objekt aufrufen: bs.send */
/* Das 1.te Argument ist dabei das Js-Objekt selbst: */
[@bs.send] external fahreAutoNach : (auto, string) => unit = "fahren";

let meineLimo: auto = createAuto("meineLimo");

Js.log(meineLimo);

fahreAutoNach(meineLimo, "Garage");

Js.log(meineLimo);

/* Vertauschen der Stelle des Js-Objekts in der Parameterliste ans Ende zum späteren Pipen: bs.send.pipe */
/* Ermöglicht Chaining */
/* [@bs.send.pipe : (Input-Typ der Chain/Pipe)]  */
/* external meineFunktion : arg => (Output-Typ der Chain/Pipe) = "(Objekt-Methode auf dem Input-Typ)"; */
[@bs.send.pipe : auto] external fahreAutoNachPiped : string => auto = "fahren";

let ente =
  createAuto("ente")
  |> fahreAutoNachPiped("CasaNoir")
  |> fahreAutoNachPiped("Hawaii")
  |> fahreAutoNachPiped("Rom");

/* *
 * */
/* Übergabe von Reason-Objekten nach JS */
/* https://bucklescript.github.io/docs/en/common-data-types.html */
[%%raw "const logMe = (object) => console.log(JSON.stringify(object))"];

[@bs.val] external logMich : array(string) => unit = "logMe";

/* Arrays */
logMich([|"erster", "zweiter", "dritter"|]);

/* Records <---> Js.t-Objekte */
[@bs.deriving jsConverter]
type testRecord = {
  x: int,
  y: int
};

let testData = {x: 4, y: 5};

[@bs.val] external logMich2 : Js.t('a) => unit = "logMe";

/* Record --> Js.t('a) */
logMich2(testRecordToJs(testData));

/* Js.t('a) --> Record */
[@bs.deriving jsConverter]
type watt = {
  was: string,
  stunden: int
};

[%%raw "const gibMal = () => ({ was: 'ist los?', stunden: 33 })"];

[@bs.val] external wattlos : unit => Js.t('a) = "gibMal";

let wattRecord = wattFromJs(wattlos());

Js.log(wattRecord.was);

Js.log(wattRecord.stunden);

/* * */
/* * */
/* Import Js-Module into Reason: */
/* Angabe eines Relative Pfads ausgehend von der erzeugten JS-Datei möglich */
/* Angabe eines Modules möglich */
/* Angabe des Modules als Methoden-Name möglich, falls Module und Funktion übereinstimmen */
/* The path needs to be relative to the outputted, generated JS-files  */
/* i.e.: lib/js/src/ */
/* Bucklescript is not a bundler. */
/* Therefore importing files are not built-in into Bucklescript */
/* but rather the existing bundler is used */
[@bs.module "../../../src/js/testModule"]
external logNochmal : string => unit = "machWas";

logNochmal("YOLO");

[@bs.module]
external isomorphicFetch : string => Js.Promise.t('a) = "isomorphic-fetch";

let handleProductData = data => {
  let names = data##products |> Array.map(p => p##name);
  Js.log("Obst-Produkte aus der API:");
  Js.log(names |> Js.Array.joinWith(", "));
};

Js.Promise.(
  isomorphicFetch("https://api.predic8.de:443/shop/products/")
  |> then_(response => response##json())
  |> then_(data => data |> handleProductData |> resolve)
);

/* *** IMPORT / REQUIRE JS-Modules in Reason */
/* *** [@bs.module "..."] */
/* *
 * */
/* Import Js-Module into ReasonML: */
[@bs.module "../../../src/js/fetcher"]
external fetch : string => Js.Promise.t(Js.t('a)) = "fetchJson";

/* Define Record-Type of response: */
[@bs.deriving jsConverter]
type fetchResponse = {
  one: string,
  key: string
};

/* Fetch + convert data from API */
Js.Promise.(
  fetch("http://echo.jsontest.com/key/value/one/two")
  |> then_(data => resolve(fetchResponseFromJs(data)))
  |> then_(recordData => {
       let {one, key} = recordData;
       Js.log({j|value with key "one" : $one
value with key "key" : $key|j})
       |> resolve;
     })
);

/* Js.Promise.(
     get("http://echo.jsontest.com/key/value/one/two")
     |> then_(response => response##json())
     |> then_(data => resolve(Js.log(data)))
   ); */
/* *
 * */
/* ### Fifty Shades of JS-Objects in Reason */
/* (1) Js.Dict : Possibly Computed Keys */
let emptyObject = Js.Dict.empty();

Js.Dict.set(emptyObject, "name", "Max Meyer");

Js.Dict.set(emptyObject, "age", "ss8");

let age =
  switch (Js.Dict.get(emptyObject, "age")) {
  | Some(a) => a
  | None => ""
  };

Js.log(age);

/* #
   # */
/* Read-Only Fields in JS-Objects: */
type jsObjectType = {
  .
  [@bs.set] "name": string,
  [@bs.set] "age": int
};

[%%bs.raw "const johnny = {name:'Johnny'};"];

[@bs.val] external johnny : jsObjectType = "johnny";

Js.log("Johnny : " ++ johnny##name);

/* #
   # */
/* Readable + Writable Fields in JS-Objects: */
/* [@bs.set] field in jsObjectType */
johnny##name#="Jane";

johnny##age#=(johnny##age + 1);

Js.log("Johnny : " ++ johnny##name);

Js.log("Age : " ++ string_of_int(johnny##age));

/* #
   # */

/****** Declare METHODS on JS-Objects: */
/* [@bs.meth] */
type jsObjectType2('a) = {. [@bs.meth] "json": unit => Js.Promise.t('a)};

type responseType2 = {
  .
  "one": string,
  "key": string
};

[%%raw "require('isomorphic-fetch')"];

[@bs.val "fetch"]
external fetch : string => Js.Promise.t(jsObjectType2(responseType2)) = "";

let dataHandler = data => {
  Js.log("self defined type -> data.one : " ++ data##one);
  Js.log("self defined type -> data.key : " ++ data##key);
};

Js.Promise.(
  fetch("http://echo.jsontest.com/key/value/one/two")
  |> then_(response => response##json())
  |> then_(data => data |> dataHandler |> resolve)
);