/*
 Pattern Matching
 */
/* Some bindings to JS: */
[@bs.module "faker"] [@bs.scope "name"]
external findName : unit => string = "findName";

[@bs.module "faker"] [@bs.scope "address"]
external findCity : unit => string = "city";

[@bs.module "faker"] [@bs.scope "company"]
external findCompanyName : unit => string = "companyName";

/*
 (1) Destructuring variants
  */
type ort =
  /* Variants as constants */
  | Hier
  | Da
  | Drueben;

let wo = Hier;

let reiseEtappe:
  /* Signature */
  ort => int =
  /* Implementation */
  ort =>
    /* Pattern matching */
    switch ort {
    /* Destructuring */
    | Hier => 1
    | _ => 2
    };

wo |> reiseEtappe |> string_of_int |> print_endline;

/*
 (2) Destructuring Variants containing values
 */
type people =
  /* Variants using Constructors as Data Containers
     (Tuple-like-style, order is important) */
  | School(int, string, string)
  | University(int, string, string)
  | Worker(int, string, string, string);

/* Helper func: f^n(arg) */
let rec apply = (n, f, arg) =>
  switch n {
  | 1 => f(arg)
  | n => apply(n - 1, f, f(arg))
  };

let generatePeople = list => {
  let age = Js.Math.random_int(0, 80);
  let name = findName();
  let city = findCity();
  switch age {
  /* Prepend new element to list: */
  /* cases using guards "when" */
  | age when age < 18 =>
    /* Reason's prepend operation via JS-like destructuring:
          [head, ...list]
       */
    [School(age, name, city), ...list]
  | age when age < 30 => [University(age, name, city), ...list]
  | age when age < 80 => [Worker(age, name, city, findCompanyName()), ...list]
  };
};

let logPeople:
  /* Signature */
  list(people) => unit =
  /* Implementation */
  ppl =>
    ppl
    /* Function Currying of List.iter into: List.iter(f) */
    |> List.iter(p
         /* Pattern Matching */
         =>
           switch p {
           /* Destructuring Variants via Constructors */
           | School(age, name, city) =>
             Js.log({j|$name, aged $age  going to school in $city|j})
           | University(age, name, city) =>
             Js.log({j|$name, aged $age going to uni in $city|j})
           | Worker(age, name, city, company) =>
             Js.log({j|$name, aged $age going to work at $company in $city|j})
           }
         );

let bunchOfPpl = apply(100, generatePeople, []);

bunchOfPpl |> logPeople;

/* Guards in Pattern Matching via switch */
type payload =
  | BadResult(int)
  | GoodResult(string)
  | NoResult;

let selectable = [|
  GoodResult("Product shipped!"),
  BadResult(500),
  BadResult(404),
  NoResult
|];

let data = selectable[Js.Math.random_int(0, Array.length(selectable))];

let isServerError = code => code >= 500;

let message =
  switch data {
  | GoodResult(_theMessage) => "gut"
  /* Guard "when": Prüfung des Falls auf eine Bedingung: */
  /* !! Erst Destructuring, um den enthaltenen Wert zu extrahieren */
  | BadResult(errorCode)
      /* !! dann den Wert prüfen mittels eines Guards */
      when isServerError(errorCode) => "schlecht"
  | BadResult(_errorCode) => "keine Ahnung"
  | NoResult => "kein Ergebnis"
  };

Js.log({j|message: $message|j});

/*
 * Exceptions und Pattern Matching
 Match on Exceptions: | exception x => ...
 If a function throws an exception (covered later), you can also match on that, in addition to the function's normally returned values.
  */
let myItems = ["item1", "item2", "item3"];

let theItem = "wasser";

switch (List.find(i => i === theItem, myItems)) {
| item => print_endline(item)
| exception Not_found => print_endline("No such item found!")
};