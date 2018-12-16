type _data = {
  id: UUID.t,
  name: string,
  description: string,
  photo: string,
  productId: Schema.FoodProduct.idAsType(Schema.modelIdType)
  

  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

let fragmentType = "MenuItem";

module ModelSchema = Schema.MenuItem;
type idType = ModelSchema.idAsType(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `MenuItemId(id);

module GraphFragment = [%graphql
  {|
    fragment menuItemFields on MenuItem {
      id
      name
      description
      photo
      product{
        ...FoodProduct.Model.Fragment.Fields
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.MenuItemFields;
};

let fragmentName = Fragment.Fields.name;
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  name: "",
  description: "",
  photo: "",
  productId: `FoodProductId(id),
  
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
      photo: obj##photo,
      description: obj##description,
      productId: obj##product |> FoodProduct.Model.objectToId,
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


