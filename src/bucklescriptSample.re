/*
 Links:
 - https://github.com/glennsl/bucklescript-cookbook

 - Bucklescript-Cheetsheet:
  https://bucklescript.github.io/docs/en/interop-cheatsheet.html
 *
 */
type auto;

/*
  * Bind the CONSTRUCTOR from JS to a Reason function:
  * - [@bs.new]
 */
[@bs.module] [@bs.new]
external createAuto : (~marke: string) => auto = "../../../src/js/auto";

let brumbrum = createAuto(~marke="BrumBrum");

Js.log(brumbrum);

/*
 Convert a Js.NULLABLE RETURN-VALUE in JS to OPTION-type in Reason
 - [@bs.return nullable]
 */
[%%raw {|const test = (input) => (input==="nix") ? undefined : "unleer"|}];

[@bs.val "test"] [@bs.return nullable]
external kannseinLeer : string => option(string) = "test";

["nix", "drin"]
|> List.map(wert =>
     switch (kannseinLeer(wert)) {
     | Some(wert) => Js.log({j|wert gefunden : $wert|j})
     | None => Js.log("wert leer")
     }
   );

/*
 * Create Js-Objekt in Reason:
 * - { "prop1" : "val" , "prop2": val }
 */
[%%bs.raw "const values = obj => Object.values(obj)"];

[@bs.val] external keys : Js.t('a) => Js.Array.t(string) = "values";

let jsObject = {"art": "test", "gueltig": true, "id": 284};

Js.log(jsObject##gueltig);

/*
  Create Js-Objekt-Types in Reason:
  - {. "field": type, "field": type }
  - mutable fields: [@bs.set]
  - Methods of Js-Objekts: [@bs.meth]
 */
type jsOb = {
  .
  [@bs.set] "name": string,
  [@bs.meth] "jubeln": unit => unit
};

[%%bs.raw
  "const obj = { name: `Rudolf`, jubeln: () => console.log(`Ich bin ${obj.name}.`)}"
];

[@bs.val] external obj : jsOb = "obj";

obj##name#="Vera";

obj##jubeln();

/*
 * import OBJECT-METHODs as functions into Reason
 * - [@bs.send] : 1st argument in function parameterlist is the object
 */
[%%bs.raw
  {|const wolf = { name: "gang", getData: (title, age, szn) =>
  `${title} wolf${wolf.name}
Alter: ${age}
Sozialversicherungsnr.: ${szn}`};|}
];

type wolf;

[@bs.val] external testObjekt : wolf = "wolf";

[@bs.send]
external getDataFromTestObject :
  (wolf, ~title: string, ~age: int, ~szn: string) => string =
  "getData";

let nameOfTestObjekt =
  testObjekt |> getDataFromTestObject(~age=54, ~szn="444", ~title="Herr");

Js.log(nameOfTestObjekt);

/*
  *  Import VARIADIC JS-functions into Reason by wrapping arguments
  *  into a Reason-Array:
  *  - [@bs.splice]
 */
[%%raw
  {|
const verpluescher = (...tiere) => tiere.map(tier => "Plüsch" + tier.toLowerCase()).join(", ")
|}
];

[@bs.val] [@bs.splice]
external verpluescher : array(string) => string = "verpluescher";

Js.log(verpluescher([|"Baer", "Hai", "Kamel", "Loewe"|]));

/*
 * import a DEFAULT function from a ES6-MODULE-EXPORT:
 * - [@bs.module "module-path"] external fn : <signature> = "default"
 */
let default = {"pommes": "fritz", "ungesund": true};

/*
 * import a DEFAULT function from a COMMONJS-MODULE-EXPORT
 * - [@bs.module] external fn : <signature> = <module-path>
 */
type fahrrad;

[@bs.module] [@bs.new]
external createFahrrad : string => fahrrad = "../../../src/js/fahrrad";
/*
  Bucklescript-Cheetsheet
  https://bucklescript.github.io/docs/en/interop-cheatsheet.html
 */