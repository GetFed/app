module GetRecord = (Model: Domain.Model) => {
  let get = (id: Schema.modelIdType): option(Model.Record.Data.t) =>
    id |> Model.getById |> Belt.Option.map(_, Model.Record.Data.fromObject);
};