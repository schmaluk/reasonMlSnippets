/*
 Awesome:
  !!In Reason you can use JSX in your Reason Code for
  function invocation.
  */
/*
 A Jsx-Component which calculates:
  Sum of f(x), where x in children and f as props
 */
let createElement = (~f: int => int, ~children=[], ()) => {
  Js.log(children);
  let initialState = 0;
  let reducer = (state, el) => state + f(el);
  List.fold_left(reducer, initialState, children);
};