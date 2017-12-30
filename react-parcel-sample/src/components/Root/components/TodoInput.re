let component = ReasonReact.statelessComponent("TodoInput");

let make = (~value, ~onChange, _children) => {
  ...component,
  render: self => <input _type="text" value onChange />
};