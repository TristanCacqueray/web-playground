// A custom hook to debug render count
let debug = (name: string): React.element => {
  // Log the event
  Js.log("[" ++ name ++ "]: rendering...");
  // Use a low level ref to mutate a local counter
  let count = React.useRef(0);
  count.current = count.current + 1;
  // Returns a react element with the render count text
  <span>
    {" [" ++ name ++ ": render count " |> React.string}
    {count.current |> React.int}
    {"] " |> React.string}
  </span>;
};
