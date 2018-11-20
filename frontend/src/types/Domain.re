module type ContainerInterface = {
  module Fragment: ApolloClient.ReadFragment;
};

module type Model = {
  type _data;
  type _local;

  type _record = RecordType.t(_data, _local);
  type idType = Schema.modelIdType;

  module rec Fragment: {
    module Fields: ReasonApolloTypes.Config;
  }
  and Record: {
    type t = _record;
    type defaultParam;
    type defaultFn = (defaultParam, Schema.modelIdType) => t;

    module Data: {
      type t = _data;
      let fromObject: Fragment.Fields.t => t;
    };
    let fromObject: Fragment.Fields.t => t;
    let defaultWithId: defaultFn;
  };

  let fragmentType: string;
  let fragmentName: string;
};

module type Container {
  type idType;
  type config;
  type record;

  let component: ReasonReact.componentSpec(
    ReasonReact.stateless,
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless
  );
  let getById: idType => option(config);
  let make:
    (~id: string,
    (~data: record) =>
    ReasonReact.reactElement) =>
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless
    );
};

module type Action = {
  type action;
  type model;
  let reduce: (action, Js.Promise.t(model)) => Js.Promise.t(model);
};

module type M = {
  module rec Model: Model
  and Action: (Action with type model = Model.Record.t);
};
