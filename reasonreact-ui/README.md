# ReasonReact UI

Run with:

```
npm install
npm run server &
npm start
```

Bundle with:

```
npm install webpack webpack-cli
./node_modules/.bin/webpack
open indexProduction.html
```


## Manual

Build with:

```
# Transpile Reason to OCaml
./node_modules/bs-platform/linux/refmt.exe -p ml src/Cli.re > cli.ml
# Compile OCaml to JS
./node_modules/bs-platform/linux/bsc.exe cli.ml > cli.js
# Compile OCaml to native
ocamlopt cli.ml -o cli
```

Run with:

```
# NodeJS
node cli.js --help
# Native
./cli --help
```

All in one:

```
bsb.exe -make-world && node src/Cli.bs.js --help
```
