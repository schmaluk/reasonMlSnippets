/* ReasonMl-fetch via Bucklescript */
/* Api: http://echo.jsontest.com/key/value/one/two */
[%%bs.raw {|require('isomorphic-fetch')|}];

/* Response Type: */
type res = {
  one: string,
  key: string
};

/* ResponseHandler: */
/* Convert: json -> record */
/* https://github.com/reasonml-community/bs-json */
/* https://stackoverflow.com/questions/43701784/how-can-i-parse-this-json-to-a-record-type */
let handleResponse = (json: Js.Json.t) => {
  let r =
    Json.Decode.{
      one: json |> field("one", string),
      key: json |> field("key", string)
    };
  let key = r.one;
  Js.log({j|
    response ist: $key
  |j});
  ();
};

/* Fetch Data from REST-API: */
/* https://github.com/reasonml-community/bs-fetch */
Js.Promise.(
  Fetch.fetch("http://echo.jsontest.com/key/value/one/two")
  /* Convert response -> text -> json */
  /* Js.Json.parseExn */
  /* |> then_(Fetch.Response.text) */
  /* |> then_(text => text |> Js.Json.parseExn |> handleResponse |> resolve) */
  /* Convert response -> json */
  |> then_(Fetch.Response.json)
  |> then_(text => text |> handleResponse |> resolve)
);