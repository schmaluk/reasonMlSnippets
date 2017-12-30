let component = ReasonReact.statelessComponent("RootHeader");

let make = _children => {
  ...component,
  render: _self =>
    <div className="jumbotron">
      <h1> (Utils.str("Todo-App-Crap in React-Reason")) </h1>
    </div>
};