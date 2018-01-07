open Materialui;

open Utils;

let component = ReasonReact.statelessComponent("Header");

let make = _children => {
  ...component,
  render: _self =>
    <AppBar> <div> (ReasonReact.stringToElement("huhu")) </div> </AppBar>
};