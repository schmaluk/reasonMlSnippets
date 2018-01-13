module IconButton = {
  [@bs.module "material-ui"]
  external buttonClass : ReasonReact.reactClass = "IconButton";
  let make =
      (
        ~classes=?,
        ~color=?,
        ~disabled=?,
        ~disableRipple=?,
        ~rootRef=?,
        ~ariaLabel=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=buttonClass,
      ~props={
        "classes": Js.Nullable.from_opt(classes),
        "color": Js.Nullable.from_opt(color),
        "disabled": Js.Nullable.from_opt(disabled),
        "disableRipple": Js.Nullable.from_opt(disableRipple),
        "rootRef": Js.Nullable.from_opt(rootRef),
        "aria-label": ariaLabel
      },
      children
    );
};

module Button = {
  [@bs.module "material-ui"]
  external buttonClass : ReasonReact.reactClass = "Button";
  let make =
      (
        ~raised: option(bool)=?,
        ~color: option(string)=?,
        ~className: option(string)=?,
        ~dense: option(bool)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=buttonClass,
      ~props={
        "raised":
          Js.Nullable.from_opt(
            Js.Option.map([@bs] (x => Js.Boolean.to_js_boolean(x)), raised)
          ),
        "color": Js.Nullable.from_opt(color),
        "className": Js.Nullable.from_opt(className),
        "dense": Js.Nullable.from_opt(dense)
      },
      children
    );
};

module AppBar = {
  [@bs.module "material-ui"]
  external appBarClass : ReasonReact.reactClass = "AppBar";
  type position =
    | Static
    | Fixed
    | Absolute;
  let toString: option(position) => option(string) =
    position =>
      switch position {
      | Some(Static) => Some("static")
      | Some(Fixed) => Some("fixed")
      | Some(Absolute) => Some("absolute")
      | None => None
      };
  let make =
      (~color=?, ~iconElementLeft=?, ~position: option(position)=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=appBarClass,
      ~props={
        "color": Js.Nullable.from_opt(color),
        "position": Js.Nullable.from_opt(toString(position))
      },
      children
    );
};

module Toolbar = {
  [@bs.module "material-ui"]
  external tbClass : ReasonReact.reactClass = "Toolbar";
  let make = (~className=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=tbClass,
      ~props={"className": Js.Nullable.from_opt(className)},
      children
    );
};

module Table = {
  [@bs.module "material-ui"]
  external tableClass : ReasonReact.reactClass = "Table";
  let make = (~classes=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=tableClass,
      ~props={"classes": classes},
      children
    );
};

module TableBody = {
  [@bs.module "material-ui"]
  external tableClass : ReasonReact.reactClass = "TableBody";
  let make = (~classes=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=tableClass,
      ~props={"classes": classes},
      children
    );
};

module TableCell = {
  type padding =
    | Default
    | Checkbox
    | Dense
    | None;
  let paddingToString: option(padding) => option(string) =
    padding =>
      switch padding {
      | Some(Default) => Some("default")
      | Some(Checkbox) => Some("checkbox")
      | Some(Dense) => Some("dense")
      | None => None
      | Some(None) => Some("none")
      };
  [@bs.module "material-ui"]
  external tableClass : ReasonReact.reactClass = "TableCell";
  let make =
      (
        ~numeric: option(bool)=?,
        ~padding: option(padding)=?,
        ~classes=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=tableClass,
      ~props={
        "classes": classes,
        "numeric": Js.Nullable.from_opt(numeric),
        "padding": Js.Nullable.from_opt(paddingToString(padding))
      },
      children
    );
};