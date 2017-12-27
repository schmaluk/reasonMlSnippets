https://github.com/yhsiang/reason-parcel-demo

1. Add dependencies: 

- `npm i -S reason-react` for using react/jsx in reason
- `npm i -D parcel-bundler` for parcel
- `npm i -D babel-preset-env` for babel

2. Add "reason-react" to your bs.config.json:
- `"bs-dependencies":["reason-react"]`
- `"reason":{"react-jsx": 2}`

3. Hook up Reason for DOM-rendering:
- Define Reason-entrypoint in `./src/index.re`:
`ReactDOMRe.renderToElementWithId(<div>(ReasonReact.stringToElement("Hello Reason and Parcel"))</div>, "root");`
- Link compiled index.js into index.html in public or lib folder: 

4. Add .babelrc-file for babel in parcel:
- `{"presets": [["env"]]}`