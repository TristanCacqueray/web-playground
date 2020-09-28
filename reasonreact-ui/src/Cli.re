type cliArgs = {verbose: bool};

let usage = (): cliArgs => {
  let verbose = ref(false);

  let spec = [
    ("--verbose", Arg.Unit(() => verbose := true), "set verbose"),
  ];

  Arg.parse(spec, ignore, "ReasonML cli!");

  {verbose: verbose^};
};

let showArgs = (cli: cliArgs) => {
  cli.verbose ? "verbose" : "silent...";
};

let cli = usage();
print_string(showArgs(cli));
