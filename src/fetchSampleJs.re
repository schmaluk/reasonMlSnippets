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

[%%bs.raw {|
    require('isomorphic-fetch');
|}];

let fetchApiResponseInline: unit => Js.Promise.t(Js.Json.t) = [%bs.raw
  {|
    ()=>fetch("http://echo.jsontest.com/key/value/one/two").then(r => r.json())
|}
];

let handleData = (data: responseType) => {
  Js.log("handleData");
  Js.log(data.one);
  Js.log(data.key);
};

/* Need to manually convert Json-data to Record-data */
/* Unfortunately there is a difference between a Bucklescript-object and Js.json.t */
let parseJsonData = (data: Js.Json.t) : responseType =>
  Json.Decode.{
    one: field("one", string, data),
    key: field("key", string, data)
  };

/* How Promises work in reason: */
/* https://jamesfriend.com.au/a-first-reason-react-app-for-js-developers */
/* https://gist.github.com/Lokeh/a8d1dc6aa2043efa62b23e559291053e */
/* promise
   |> Js.Promise._then(value1 => promise1)
   |> Js.Promise._then(value2 => promise2)
   |> Js.Promise._then(value3 => Js.Promise.resolve(doSthgWith(value3))) */
fetchApiResponseInline()
|> Js.Promise.then_(data
     /* Need to return a Promise to fullfil expected function signature in then_(...) */
     => Js.Promise.resolve(handleData(parseJsonData(data))));