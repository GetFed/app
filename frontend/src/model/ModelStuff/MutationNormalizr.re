module GetRecord = (
  Model: Domain.Model,
  Container: Domain.Container
      with type idType = Model.idType
      and type record = Model.Record.t
      and type config = Model.Fragment.Fields.t,
) => {
  let get = (id: Schema.modelIdType): option(Model.Record.Data.t) =>
    id |> Container.getById |> Belt.Option.map(_, Model.Record.Data.fromObject);
};