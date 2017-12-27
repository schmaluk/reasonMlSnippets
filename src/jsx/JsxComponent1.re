/*
 Reason-React:
 - https://reasonml.github.io/reason-react/docs/en/installation.html
 - https://reasonml.github.io/guide/language/jsx
 */
/* Configuring bs.json for React-Reason:
      - Put {"reason": {"react-jsx": 2}} in your bsconfig.json
      - see: https://reasonml.github.io/reason-react/docs/en/jsx.html
   */
let component = ReasonReact.statelessComponent("TodoApp");

let make = children => {
  ...component,
  render: self =>
    <div className="app">
      <div className="title">
        (ReasonReact.stringToElement("What to do"))
      </div>
      <div className="items"> (ReasonReact.stringToElement("Nothing")) </div>
    </div>
};