type recordType = NormalizrRecordType.t;
let modelTypeToRecordType = NormalizrRecordType.modelTypeToRecordType;

module type DomainWrapper = {
  type model;
  let wrap: model => recordType;
  let unwrap: recordType => option(model);
  let apolloEnabled: bool;
};

type normalizedType =
  NormalizrNew.normalizedSchema(Schema.schemaType, UUID.t, recordType);

let normalizerCommitItemToSchema:
  (normalizedType, recordType) => normalizedType =
  NormalizrNew.Normalizr.commitItemToSchema(modelTypeToRecordType);

let normalizerGetItemFromSchema:
  (normalizedType, Schema.modelIdType) => option(recordType) =
  NormalizrNew.Normalizr.getItemFromSchema(Schema.modelIdToIdFunction);

let idListToFilteredItems =
    (idList: list(Schema.modelIdType), modelTypefunction) =>
  idList
  |> Belt.List.map(_, modelTypefunction)
  |> Utils.List.removeOptionsFromList;

let tryAgainifNullOption = (optionA, optionB) =>
  switch (optionA) {
  | Some(_) => optionA
  | None => optionB
  };

module DomainTypeConverter =
  (
    DomainType: Domain.M,
    Container: Domain.Container
      with type idType = DomainType.Model.idType
      and type record = DomainType.Model.Record.t
      and type config = DomainType.Model.Fragment.Fields.t,
    Wrapper: DomainWrapper with type model = DomainType.Model.Record.t,
  ) => {
  let update =
      (
        default: Schema.modelIdType => DomainType.Model.Record.t,
        getterFn:
          (normalizedType, Schema.modelIdType) =>
          option(DomainType.Model.Record.t),
        reduce:
          (DomainType.Action.action, Js.Promise.t(DomainType.Action.model)) =>
          Js.Promise.t(DomainType.Action.model),
        normalized: Js.Promise.t(normalizedType),
        id: Schema.modelIdType,
        action: DomainType.Action.action,
      ) : Js.Promise.t(normalizedType) => {
    normalized
    |> Js.Promise.then_(norm =>
        norm
        |> getterFn(_, id)
        |> Belt.Option.getWithDefault(_, default(id))
        |> Js.Promise.resolve)
    |> reduce(action, _)
    |> (modelPromise) => (normalized, modelPromise)
    |> Js.Promise.all2
    |> Js.Promise.then_(((norm, model)) =>
        Js.Promise.resolve(normalizerCommitItemToSchema(norm, Wrapper.wrap(model))));
  };
  let fromLocal =
      (
        normalized: normalizedType,
        id: Schema.modelIdType /* maybe make domain model idtype*/,
      )
      : option(DomainType.Model.Record.t) =>
    normalized
    |> normalizerGetItemFromSchema(_, id)
    |> Belt.Option.flatMap(_, Wrapper.unwrap);

  let fromSchema =
      (
        normalized: normalizedType,
        id: Schema.modelIdType /* maybe make domain model idtype*/,
      )
      : option(DomainType.Model.Record.t) => {
    let optionNormalized = fromLocal(normalized, id);

    Wrapper.apolloEnabled ?
      id
      |> Container.getById
      |> Belt.Option.map(_, (fragment: DomainType.Model.Fragment.Fields.t) =>
           (
             switch (optionNormalized) {
             | Some(data) => {
                 local: data.local,
                 data: DomainType.Model.Record.Data.fromObject(fragment),
               }
             | None => DomainType.Model.Record.fromObject(fragment) /* does this also generate the local? */
             }: DomainType.Model.Record.t
           )
         )
      |> tryAgainifNullOption(_, optionNormalized) :
      optionNormalized;
  };

  module Local = {
    let getRecord = fromLocal;
    let getRecordWithDefault =
        (
          normalized: normalizedType,
          id: Schema.modelIdType,
          param: DomainType.Model.Record.defaultParam,
        )
        : DomainType.Model.Record.t =>
      normalized
      |> fromLocal(_, id)
      |> Belt.Option.getWithDefault(
           _,
           DomainType.Model.Record.defaultWithId(param, id),
         );

    let updateWithDefault = (param: DomainType.Model.Record.defaultParam) =>
      update(
        DomainType.Model.Record.defaultWithId(param, _),
        fromLocal,
        DomainType.Action.reduce,
      );
  };

  module Remote = {
    let getRecord = fromSchema;
    let getRecordWithDefault =
        (
          normalized: normalizedType,
          id: Schema.modelIdType,
          param: DomainType.Model.Record.defaultParam,
        )
        : DomainType.Model.Record.t =>
      normalized
      |> fromSchema(_, id)
      |> Belt.Option.getWithDefault(
           _,
           DomainType.Model.Record.defaultWithId(param, id),
         );

    let updateWithDefault = (param: DomainType.Model.Record.defaultParam) =>
      update(
        DomainType.Model.Record.defaultWithId(param, _),
        fromSchema, /* How does this handle the llocal??????? */
        DomainType.Action.reduce,
      );
  };
};