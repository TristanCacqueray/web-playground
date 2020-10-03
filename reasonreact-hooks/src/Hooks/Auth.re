// From https://dev.to/margaretkrutikova/reason-react-context-explained-in-action-5eki
type auth = {user: string}
and status =
  | Anonymous
  | Authenticated(auth)
and action =
  | Login(auth)
  | Logout;

let showState = (status: status): string =>
  switch (status) {
  | Anonymous => "Stranger"
  | Authenticated(auth) => auth.user
  };

// use wrap the useReducer hook
let use = () => {
  let (state, dispatch) =
    React.useReducer(
      (_state, action) =>
        switch (action) {
        | Login(auth) => Authenticated(auth)
        | Logout => Anonymous
        },
      Anonymous,
    );
  (state, dispatch);
};

// Create the context
let context = React.createContext(Anonymous);

// useAuth simply wrap the useContext hook
let useAuth = () => React.useContext(context);

module Provider = {
  let make = React.Context.provider(context);

  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
};

// A fake login menu component
module Menu = {
  [@react.component]
  let make = (~state, ~dispatch) => {
    <>
      <span>
        {"Welcome " |> React.string}
        {state |> showState |> React.string}
      </span>
      {" " |> React.string}
      <button onClick={_ => dispatch(Login({user: "admin"}))}>
        {"Login as admin" |> React.string}
      </button>
      <button onClick={_ => dispatch(Login({user: "alice"}))}>
        {"Login as alice" |> React.string}
      </button>
      <button onClick={_ => dispatch(Logout)}>
        {"Logout" |> React.string}
      </button>
    </>;
  };
};
