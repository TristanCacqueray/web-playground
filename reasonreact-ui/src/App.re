let url = "http://localhost:3000/api/info";

[@react.component]
let make = () => {
  <div>{"hello" |> React.string}
  <Menu url/>
  </div>;
};
