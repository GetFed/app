type _data = {
  id: UUID.t,
  /* UI */
  restrictionIds: option(list(option(Schema.Restriction.idAsType(Schema.modelIdType)))),
  ingredientIds: list(option(Schema.Ingredient.idAsType(Schema.modelIdType))),
  attributeIds: list(option(Schema.Attribute.idAsType(Schema.modelIdType))),
  nutritionFactsId: Schema.NutritionFacts.idAsType(Schema.modelIdType)
};

type _local = unit;
type _record = RecordType.t(_data, _local);

let fragmentType = "Food";
let fragmentName = "foodFields";
module ModelSchema = Schema.Food;
type idType = ModelSchema.idAsType(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `FoodId(id);

module GraphFragment = [%graphql
  {|
    fragment foodFields on Food {
      id
      restrictions {
        edges {
          node {
            ...Restriction.Model.Fragment.Fields
          }
        }
      }
      nutritionFacts {
        ...NutritionFacts.Model.Fragment.Fields
      }
      attributes {
        edges {
          node {
            ...Attribute.Model.Fragment.Fields
          }
        }
      }
      ingredients {
        edges {
          node {
            ...Ingredient.Model.Fragment.Fields
          }
        }
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.FoodFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  /* UI */
  restrictionIds: None,
  ingredientIds: [],
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
      nutritionFactsId: obj##nutritionFacts |> NutritionFacts.Model.objectToId,
      restrictionIds:
        obj##restrictions
        |> Belt.Option.map(_, (res) => ModelUtils.getConnectionList(res, Restriction.Model.objectToId)),
      ingredientIds:
        obj##ingredients
        |> ModelUtils.getConnectionList(_, Ingredient.Model.objectToId),
      attributeIds:
        obj##attributes
        |> ModelUtils.getConnectionList(_, Attribute.Model.objectToId),
    };
  };

  let default = () => _defaultRecord();
  let defaultWithId = ((), id): t =>
    _defaultRecordId(id |> Schema.getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: (),
  };
};


