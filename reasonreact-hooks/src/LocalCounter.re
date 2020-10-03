// A reason-react example of a counter implemented with useState
type state = {count: int};

[@react.component]
let make = () => {
  let (count, setCount) = React.useState(_ => 0);
  <>
    {RenderCount.debug("LocalCounter")}
    {React.string("Count: " ++ string_of_int(count))}
    <button onClick={_ => setCount(_ => 0)}> {React.string("Reset")} </button>
    <button onClick={_ => setCount(prevCount => prevCount - 1)}>
      {React.string("-")}
    </button>
    <button onClick={_ => setCount(prevCount => prevCount + 1)}>
      {React.string("+")}
    </button>
  </>;
};
