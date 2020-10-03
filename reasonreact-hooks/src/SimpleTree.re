// A test of useState and React.memo

module SimpleLeaf = {
  // This component doesn't have prop, use `memo` to skip re-render when parent change
  [@react.component]
  let make =
    React.memo(() => {<p> {RenderCount.debug("Tree.SimpleLeaf")} </p>});
};

module DependentLeaf = {
  // This component should re-render when prop change
  [@react.component]
  let make = (~value: int) => {
    <p> {RenderCount.debug("Tree.DependentLeaf")} {value |> React.int} </p>;
  };
};

// A component that has a state and two leafs
[@react.component]
let make = () => {
  let (value, setValue) = React.useState(_ => 0);
  <>
    {RenderCount.debug("Tree")}
    <button onClick={_ => setValue(prevCount => prevCount + 1)}>
      {React.string("change")}
    </button>
    <SimpleLeaf />
    <DependentLeaf value />
  </>;
};
