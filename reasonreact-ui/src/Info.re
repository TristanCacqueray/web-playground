type info = {services: list(service)}
and service = {
  name: string,
  path: string,
};

module Decode = {
  let service = json =>
    Json.Decode.{
      name: json |> field("name", string),
      path: json |> field("path", string),
    };

  let info = json =>
    Json.Decode.{services: json |> field("services", list(service))};
};

let show = (info: info): string => {
  String.concat(
    " ",
    ["Number of services: ", info.services |> List.length |> string_of_int],
  );
};

let show_print = info => show(info) |> print_string;

let fetchServices = (url: string): Js.Promise.t(info) =>
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(json => json |> Decode.info |> resolve)
  );
