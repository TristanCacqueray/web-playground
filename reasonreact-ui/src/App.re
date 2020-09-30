let url = "http://localhost:3000/api/info";

[@react.component]
let make = () => {
  <div>
    {"ReasonML UI" |> React.string}
    <Menu url />
    <Button variant="primary" onClick=Js.log>
      {"Button" |> React.string}
    </Button>
    <SimpleModal />
  </div>;
};
