/* Js-fetch via Js-Interop */
/* Api: http://echo.jsontest.com/key/value/one/two */
/* Define Interface to Js-function */
/* https://reasonml.github.io/guide/javascript/interop/ */
/* https://jaredforsyth.com/2017/06/03/javascript-interop-with-reason-and-bucklescript/ */
/* Bucklescript-Object vs ReasonML-Object: */
/* https://reasonml.github.io/guide/language/object/ */
[@bs.deriving jsConverter]
/* Conversion: JS-Object <--> Record */
type responseType = {
  one: string,
  key: string
};

let test = {"one": "einsie", "key": "schl\195\188ssli"};

let converted = responseTypeFromJs(test);

Js.log(converted);

[%%bs.raw {|
    require('isomorphic-fetch');
|}];

/* fetch("http://echo.jsontest.com/key/value/one/two").then(r => r.text()) */
let fetchApiResponseInline: unit => Js.Promise.t(Js.Json.t) = [%bs.raw
  {|
    ()=>Promise.resolve({one:"dadad", key: "dsdsd"})
|}
];

let handleResponse = data => {
  Js.log("handleRessssponse");
  Js.log(data);
};

/* How Promises work in reason: */
/* https://jamesfriend.com.au/a-first-reason-react-app-for-js-developers */
/* https://gist.github.com/Lokeh/a8d1dc6aa2043efa62b23e559291053e */
/* promise
   |> Js.Promise._then(value1 => promise1)
   |> Js.Promise._then(value2 => promise2)
   |> Js.Promise._then(value3 => Js.Promise.resolve(value3)) */
fetchApiResponseInline()
|> Js.Promise.then_(data => Js.Promise.resolve(data))
|> Js.Promise.then_(data => Js.Promise.resolve(Js.log(data)));