// This module manage application context, e.g. fetch from an `/api/info` endpoint
// The info type contains global value such as server version or list of capabilities
type info = {version: string}
and status =
  | Loading
  | Loaded(info);

// This function wraps useState and useEffects, and it only returns the value
let get = (~delay=0, ()) => {
  // Use a local state to store
  let (info, setInfo) = React.useState(() => Loading);
  // Run an effect to get the info
  React.useEffect0(() => {
    Js.log("Fetching info...");
    let fakeInfo = {version: "4.2"};
    ignore(
      Js.Global.setTimeout(
        () => setInfo(_ => Loaded(fakeInfo)),
        delay * 1000,
      ),
    );
    None;
  });
  // Return the status, hidding the state and the effect
  info;
};
