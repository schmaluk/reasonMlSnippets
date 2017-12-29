# Links:
- https://github.com/yhsiang/reason-parcel-demo
- https://parceljs.org/getting_started.html

# Manually setting up Parcel with ReasonML and React:
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
- Link the compiled entrypoint index.js into index.html in (private) lib-folder: `<script src="js/src/index.bs.js"></script>`

4. Add .babelrc-file to project-root-folder for babel used by parcel:
- `{"presets": [["env"]]}`

5. Run Parcel with entrypoint:
- `parcel ./lib/index.html`

# Parcel
- Parcel will resolve all separated modules containing heterogenous dependency types (js, html, css, scss, etc...) starting from the entrypoint and create a public ./dist-folder from where the bundle is being served. For bundling it uses the typical config-files depending on the module-type (.babelrc for js, etc...)

# Definition of Bundling
- The source code of a web app is usually split up into several modules of different types and those modules are referencing each other (html -> js -> css) creating kind of a tree. Bundling describes the process of merging all separated modules into
a single bundle-file which can be then served as a static asset by the webserver.