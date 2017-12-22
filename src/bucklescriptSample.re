/* https://bucklescript.github.io/bucklescript/Manual.html#_binding_to_method_code_bs_send_code_code_bs_send_pipe_code
 */
/* https://github.com/glennsl/bucklescript-cookbook */
/* Ziel von Bucklescript unter Reason ist es, type-safe JS-Objekte zu importieren/aufzurufen aus Reason heraus */
/* D.h. Ziel von Bucklescript unter Reason: FFI */
/* (1) [@bs.send] Objekt-Methode als Funktion unter Reason aufrufen */
/* (2) [@bs.send.pipe: inputTyp] Objekt-Methode als Pipe-Funktion unter Reason aufrufen */
/* (3) [@bs.val] Werte im JS-Scope nach Reason importieren */
/* (4) [@bs.module "rel.Pfad oder ModulName"] Funktionen aus JS-Modulen nach Reason importieren */
/* Typ-Deklaration eines JS-Objekts unter Reason : Js.XYZ.t */
/* type jsObjectType = {
     .
     "name": string,
     "age": int,
     [@bs.meth] "sprechen": string => unit
   }; */
/* (5) Define Types for JS-Objects in Reason: */
/* let obj: jsObjectType = {
     "name": "Max",
     "age": 99,
     "sprechen": (x: string) => Js.log(x)
   }; */
/* Accessing fields of a JS-Object in Reason & Bucklescript: */
/* Fields are not settable aka mutable by default: !!! obj##name #= "" */
/* JS-Konstruktor-Aufruf: [@bs.new] */
type auto;

/* Bind Constructor call from JS to a Reason function: [@bs.new] */
/* JS-module with a default export */
[@bs.module] [@bs.new]
external createAuto : string => auto = "../../../src/js/auto";

let brumbrum = createAuto("BrumBrum");

Js.log(brumbrum);