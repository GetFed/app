module Container = (
  ReadFragment: ApolloClient.ReadFragment,
  Model: Domain.Model
): (
  Domain.Container
    with type record = Model.Record.t
    and type config = Model.Fragment.Fields.t
    and type idType = Model.idType
  ) => {

  /* (Action with type model = Model.Record.t) */

  type record = Model.Record.t;
  type config = Model.Fragment.Fields.t;
  type idType = Model.idType;

  module FragmentConfig = ReadFragment(Model.Fragment.Fields);
  
  module InnerContainer = {
    let component = ReasonReact.statelessComponent("ApolloFragmentContainer");
    let get = (~fragmentType: string, ~id: string, ~fragmentName: string): option(config) =>
      FragmentConfig.read(
        ~client=Client.apiInstance,
        ~id=fragmentType ++ ":" ++ id,
        ~fragmentName,
        (),
      );

    let make = (
      ~fragmentType: string,
      ~id: string,
      ~failComponent: option(ReasonReact.reactElement)=?,
      ~fragmentName: string,
      children: (~data: config) => ReasonReact.reactElement
    ) : ReasonReact.componentSpec(
          ReasonReact.stateless,
          ReasonReact.stateless,
          ReasonReact.noRetainedProps,
          ReasonReact.noRetainedProps,
          ReasonReact.actionless
        ) => {
      ...component,
      render: _ =>
        switch (get(~fragmentType, ~id, ~fragmentName)) {
        | None =>
          switch (failComponent) {
          | None => ReasonReact.string("No data Loaded")
          | Some(comp) => comp
          }
        | Some(data) => children(data)
        },
    };
  }

  let getById = (id: idType) : option(config) =>
      InnerContainer.get(
        ~fragmentType=Model.fragmentType,
        ~fragmentName=Model.fragmentName,
        ~id=Model.getUUIDFromId(id)
      );

  let getRecordById = (id: idType) : option(Model.Record.t) =>
    InnerContainer.get(
      ~fragmentType=Model.fragmentType,
      ~fragmentName=Model.fragmentName,
      ~id=Model.getUUIDFromId(id)
    )
    |> Belt.Option.map(_, Model.Record.fromObject);

  let component = ReasonReact.statelessComponent(Model.fragmentType ++ "Container");

  let make = (~id, children) => {
    ...component,
    render: _ =>
      <InnerContainer fragmentType=Model.fragmentType id fragmentName=Model.fragmentName>
        ...{(~data : Model.Fragment.Fields.t) =>
          children(data |> Model.Record.fromObject)}
      </InnerContainer>,
  };
};