/*
 - https://reasonml.github.io/reason-react/docs/en/installation.html
 - https://reasonml.github.io/guide/language/jsx
 - !!! very good one !! https://jaredforsyth.com/2017/07/05/a-reason-react-tutorial/
 */
/* Add the following to bsconfig.json:
      (1) "react-jsx"
       "reason": {
           "react-jsx": 2
       }
      (2) Install "reason-react": npm i -S reason-react
       "bs-dependencies": [
            "reason-react"
       ]
   */
let component = ReasonReact.statelessComponent("TodoApp");

let make = children => {...component, render: self => <JsxComponent1 />};