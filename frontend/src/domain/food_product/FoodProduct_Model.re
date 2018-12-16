type _data = {
  id: UUID.t,
  productId: Schema.ProductBase.idAsType(Schema.modelIdType),
  foodId: Schema.Ingredient.idAsType(Schema.modelIdType),
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

let fragmentType = "FoodProduct";

module ModelSchema = Schema.FoodProduct;
type idType = ModelSchema.idAsType(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `FoodProductId(id);

module GraphFragment = [%graphql
  {|
    fragment foodProductFields on FoodProduct {
      id
      food{
        ...Ingredient.Model.Fragment.Fields
      }
      product{
        ...ProductBase.Model.Fragment.Fields
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.FoodProductFields;
};

let fragmentName = Fragment.Fields.name;
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  productId: `ProductBaseId(id),
  foodId: `IngredientId(id),
  
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
      productId: obj##product |> ProductBase.Model.objectToId,
      foodId: obj##food |> Ingredient.Model.objectToId,
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
