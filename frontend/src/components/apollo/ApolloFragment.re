let component = ReasonReact.statelessComponent("ApolloFragmentContainer");

module Container =
       (Fragment: ApolloClient.ReadFragment, Config: ReasonApolloTypes.Config) => {
  module FragmentConfig = Fragment(Config);

  let get = (~fragmentType, ~id, ~fragmentName) =>
    FragmentConfig.read(
      ~client=Client.apiInstance,
      ~id=fragmentType ++ ":" ++ id,
      ~fragmentName,
      (),
    );

  let make = (~fragmentType, ~id, ~failComponent=?, ~fragmentName, children) => {
    ...component,
    render: _ =>
      switch (get(~fragmentType, ~id, ~fragmentName)) {
      | None =>
        switch (failComponent) {
        | None => ReasonReact.string("No data Loaded")
        | Some(comp) => comp
        }
      | Some(data) => children(~data)
      },
  };
};