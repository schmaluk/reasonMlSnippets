# Links:
- https://github.com/yhsiang/reason-parcel-demo
- https://parceljs.org/getting_started.html

# Setting up Parcel with ReasonML and React:
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
- Link compiled index.js into index.html in (private) lib-folder: `<script src="js/src/index.bs.js"></script>`

4. Add .babelrc-file to project-root-folder for babel used by parcel:
- `{"presets": [["env"]]}`

5. Run Parcel with entrypoint:
- `parcel ./lib/index.html`

# Parcel
- Parcel will resolve all separated modules containing heterogenous dependency types (js, html, css, scss, etc...) starting from the entrypoint and creates a public ./dist-folder where the created bundle is being served. For creating the bundle it uses the typical config-files depending on the type (.babelrc, etc...)

# Definition of Bundling
- The source code of a web app is usually splitted up into several modules and those modules are referencing each other (html -> js -> css). Bundling describes the process of merging all those separated modules into
a single bundle-file which can be served as a static asset by a webserver.