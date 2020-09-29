// Run npm install --no-save isomorphic-fetch   to enable nodejs usage
[%raw "require('isomorphic-fetch')"];

type cliArgs = {
  verbose: bool,
  url: string,
};

let usage = (): cliArgs => {
  let verbose = ref(false);
  let url = ref(App.url);

  let spec = [
    ("--verbose", Arg.Unit(() => verbose := true), "set verbose"),
    ("--url", Arg.String(arg => url := arg), "api url"),
  ];

  Arg.parse(spec, ignore, "ReasonML cli!");

  {verbose: verbose^, url: url^};
};

let showArgs = (cli: cliArgs) => {
  cli.verbose ? "verbose" : "silent...";
};

let cli = usage();
Info.fetchServices(cli.url)
|> Js.Promise.then_(info => {info |> Info.show_print |> Js.Promise.resolve});
