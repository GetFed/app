type _data = {
  id: UUID.t,
  name: string,
  /* UI */
  restrictionIds: option(list(option(Schema.Restriction.id))),
  attributeIds: list(option(Schema.Attribute.id)),
  nutritionFactsId: Schema.NutritionFacts.id
};

/* GraphQL doesn't support spread recursion */
/* https://github.com/facebook/graphql/issues/91 */
/* TODO if this ever gets changed remove this model */

type _local = unit;
type _record = RecordType.t(_data, _local);

module ModelSchema = Schema.IngredientBaseSpread;
type idType = ModelSchema.id;
type rootIdType = ModelUtils.RootModel.id;
let idToRootId = ModelSchema.idToRootId;
let getUUIDFromId = ModelSchema.idToString;
let idToTypedId = (id: UUID.t): idType => ModelSchema.stringToId(id);

module Fragment = IngredientBaseSpread_Fragment;
let fragmentType = Fragment.fragmentType;
let fragmentName = Fragment.Fields.name;
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

/* ^ can't be recursive because it would be an infinite object */



let _defaultData = id => {
  id: id,
  name: "",
  /* UI */
  restrictionIds: None,
  attributeIds: [],
  nutritionFactsId: NutritionFacts.Model.idToTypedId(id),
};

let _defaultRecordId = id: _record => {
  data: _defaultData(id),
  local: (),
};

let _defaultRecord = (): _record => _defaultRecordId(UUID.generateUUID());

module Record = {
  type t = _record;
  type defaultParam = unit;
  type defaultFn = (defaultParam, idType) => t;

  module Data = {
    type t = _data;
    let fromObject = (obj: Fragment.Fields.t): t => {
      id: obj##id,
      name: obj##name,
      nutritionFactsId: obj##nutritionFacts |> NutritionFacts.Model.objectToId,
      restrictionIds:
        obj##restrictions
        |> Belt.Option.map(_, (res) => ModelUtils.getConnectionList(res, Restriction.Model.objectToId)),
      attributeIds:
        obj##attributes
        |> ModelUtils.getConnectionList(_, Attribute.Model.objectToId),
    };
  };

  let default = () => _defaultRecord();
  let defaultWithId = ((), id): t =>
    _defaultRecordId(id |> getUUIDFromId);
  let findId = (record : _record) => record.data.id;

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: (),
  };
};


