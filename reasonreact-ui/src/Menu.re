type state =
  | Loading
  | Failure
  | Success(list(Info.service));

[@react.component]
let make = (~url) => {
  let (state, setState) = React.useState(() => Loading);
  let getServices = (info: Info.info) => info.services;
  React.useEffect0(() => {
    Js.Promise.(
      Info.fetchServices(url)
      |> then_(info => {
           setState(_ => Success(getServices(info))) |> resolve
         })
      |> catch(_err => setState(_ => Failure) |> resolve)
      |> ignore
    );
    None;
  });
  <ul>
    {switch (state) {
     | Loading => <li> {"Loading..." |> React.string} </li>
     | Failure => <li> {"Couldn't fetch menu..." |> React.string} </li>
     | Success(services) =>
       services
       ->Belt.List.map(service =>
           <li key={service.name}>
             <a href={service.path}> {service.name |> React.string} </a>
           </li>
         )
       ->Belt.List.toArray
       ->React.array
     }}
  </ul>;
};
