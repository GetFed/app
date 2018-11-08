module type Model = {
  type idType;
  type _data;
  type _local;

  type _record = RecordType.t(_data, _local);

  module rec Fragment: {module Fields: {type t;};}
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
  let getById: Schema.modelIdType => option(Fragment.Fields.t);
};

module type Action = {
  type action;
  type model;
  let reduce: (action, Js.Promise.t(model)) => Js.Promise.t(model);
};

module type M = {
  module rec Model: Model
  and Action: Action with type model = Model.Record.t;
};
