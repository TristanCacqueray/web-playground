// Some simple compoments
module ColorDiv = {
  [@react.component]
  let make = (~color, ~children) => {
    <div
      style={ReactDOM.Style.make(
        ~background=color,
        ~padding="5px",
        ~margin="1px",
        (),
      )}>
      children
    </div>;
  };
};

module ShowLoading = {
  [@react.component]
  let make = () =>
    <ColorDiv color="lightblue">
      {RenderCount.debug("ShowLoading")}
      {"Loading" |> React.string}
    </ColorDiv>;
};

// A welcome component that useAuth to get auth status
module Welcome = {
  [@react.component]
  let make = () => {
    React.useEffect(() => {
      Js.log("Welcome.MainEffect!");
      None;
    });

    let auth = Auth.useAuth();
    switch (auth) {
    | Anonymous => <span> {"Anon user" |> React.string} </span>
    | Authenticated(auth) =>
      auth.user == "admin"
        ? <button> {"Admin Action" |> React.string} </button>
        : <span> {"Regular user" |> React.string} </span>
    };
  };
};

module About = {
  [@react.component]
  let make =
    React.memo(() => {
      React.useEffect(() => {
        Js.log("AboutEffect!");
        None;
      });

      <> {RenderCount.debug("App.About")} {"About info" |> React.string} </>;
    });
};

// The Main app component that combine an Auth.Menu, the Welcome component and a dump About div
module Main = {
  [@react.component]
  let make = (~info: Infos.info) => {
    let (state, dispatch) = Auth.use();
    <Auth.Provider value=state>
      <ColorDiv color="lightgreen">
        {RenderCount.debug("Main")}
        {"Application version " ++ info.version |> React.string}
        <ColorDiv color="lightpink">
          {RenderCount.debug("Auth.Menu")}
          <Auth.Menu state dispatch />
        </ColorDiv>
        <ColorDiv color="lightblue"> <About /> </ColorDiv>
        <ColorDiv color="lightcyan">
          {RenderCount.debug("Welcome")}
          <Welcome />
        </ColorDiv>
      </ColorDiv>
    </Auth.Provider>;
  };
};

[@react.component]
let make = () => {
  <div>
    <h1>
      {RenderCount.debug("Title")}
      {"ReasonML React Reducer demo" |> React.string}
    </h1>
    {switch (Infos.get(~delay=1, ())) {
     | Infos.Loading => <ShowLoading />
     | Infos.Loaded(info) => <Main info />
     }}
    <ColorDiv color="lightgrey"> <LocalCounter /> </ColorDiv>
    <ColorDiv color="darkcyan"> <SimpleTree /> </ColorDiv>
  </div>;
};
