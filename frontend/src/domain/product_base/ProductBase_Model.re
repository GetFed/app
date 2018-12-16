type _data = {
  id: UUID.t,
  price: float,
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

let fragmentType = "ProductBase";
module ModelSchema = Schema.ProductBase;
type idType = ModelSchema.idAsType(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `ProductBaseId(id);

module GraphFragment = [%graphql
  {|
    fragment productBaseFields on ProductBase {
      id
      price
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.ProductBaseFields;
};

let fragmentName = Fragment.Fields.name;
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  /* UI */
  price: 0.,
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
      price: obj##price,
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


