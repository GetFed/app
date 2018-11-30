type _data = {
  id: UUID.t,
  name: string,
  price: float,
  description: string,
  photo: string,
  restrictionIds: option(list(option(Schema.restrictionId(Schema.modelIdType)))),
  ingredientIds: list(option(Schema.ingredientId(Schema.modelIdType))),
  attributeIds: list(option(Schema.attributeId(Schema.modelIdType))),
  nutritionFactsId: Schema.nutritionFactsId(Schema.modelIdType)

  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

type idType = Schema.menuItemId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `MenuId(id);

module GraphFragment = [%graphql
  {|
    fragment menuItemFields on MenuItem {
      id
      name
      description
      price
      photo
      restrictions {
        edges {
          node {
            ...Restriction.Model.Fragment.RestrictionFields
          }
        }
      }
      nutritionFacts {
        ...NutritionFacts.Model.Fragment.NutritionFactsFields
      }
      attributes {
        edges {
          node {
            ...Attribute.Model.Fragment.AttributeFields
          }
        }
      }
      ingredients {
        edges {
          node {
            ...Ingredient.Model.Fragment.IngredientFields
          }
        }
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.MenuItemFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  name: "",
  description: "",
  photo: "",
  price: 0.,
  restrictionIds: None,
  ingredientIds: [],
  attributeIds: [],
  nutritionFactsId: NutritionFacts.Model.idToTypedId(id),
  /* UI */
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
      price: obj##price,
      photo: obj##photo,
      description: obj##description,
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

let fragmentType = "MenuItem";

let fragmentName = "menuItemFields";
