open Utils;

open Materialui;

/* type */
type state = {expanded: bool};

/* state */
let initialState = {expanded: true};

/* actions */
type actions =
  | Open
  | Close;

let component = ReasonReact.reducerComponent("Root");

/* Your familiar handleClick from ReactJS. This mandatorily takes the payload,
   then the `self` record, which contains state (none here), `handle`, `reduce`
   and other utilities */
let handleClick = (_event, _self) => Js.log("clicked!");

/* `make` is the function that mandatorily takes `children` (if you want to use
   `JSX). `message` is a named argument, which simulates ReactJS props. Usage:

   `<Page message="hello" />`

   Which desugars to

   `ReasonReact.element(Page.make(~message="hello", [||]))` */
let make = (~message, _children) => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch action {
    | Open => ReasonReact.Update({...state, expanded: true})
    | Close => ReasonReact.Update({...state, expanded: false})
    | _ => ReasonReact.NoUpdate
    },
  render: self =>
    <AppBar>
      <Toolbar>
        <IconButton color="contrast" ariaLabel="Menu">
          (ReasonReact.stringToElement("face"))
        </IconButton>
        <Button raised=true> (ReasonReact.stringToElement("Click")) </Button>
      </Toolbar>
    </AppBar>
};