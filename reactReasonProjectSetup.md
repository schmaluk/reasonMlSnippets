# Project setup with React-Reason:
## (1) Bucklescript + Webpack:
- `bsb -init <project-folder-name> -theme react`
- Will create a local index.html-file in project root folder to be opened locally in the browser without a dev-webser
- `npm run start` for starting bucklescript-file-watcher to compile Reason code: `src/*.re -> lib/*.js`
- `npm run webpack` for starting webpack-file-watcher  to bundle buckescript-compiled-js-files: `lib/*.js -> build/index.js`

## (2) Bucklescript + Parcel
- `bsb -init <project-folder-name> -theme basic-reason` 
- Will create a project-folder with bucklescript (bsconfig.json)
- `npm i -S reason-react react react-dom`
- Add `"reason": {"react-jsx": 2}` and `"bs-dependencies": ["reason-react"]` to your bsconfig.json
- `npm i -D parcel-bundler` https://parceljs.org/getting_started.html
- Create entrypoint-file for parcel-bundler `index.re` with:
`ReactDOMRe.renderToElementWithId(<div>(ReasonReact.stringToElement("message"))</div>, "root");`
- Create `index.html`-file in project-root or wherever with rendertarget for react: `<div id="root"></div>` and link to js-entrypoint-file (!not the bundle-file created by parcel): `<script src="src/index.bs.js"></script>`
- Add npm-script to package.json for parcel-bundler: `"parcel": "parcel index.html"`
- `npm run start` for starting bucklescript-file-watcher
- `npm run parcel` for starting parcel-web-dev-server
- Local dev webserver starts at localhost:1234

## (3) Use create-react-app (webpack behind the curtains)
- Had some problems using it, also more bloated compared to other ways above
- `sudo create-react-app <app-name> --scripts-version reason-scripts`
- `npm run start`
- Will start local dev webserver at localhost:3000