type _data = {
  id: UUID.t,
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

module ModelSchema = Schema.Customer;
type idType = ModelSchema.idAsType(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `CustomerId(id);

module GraphFragment = [%graphql
  {|
    fragment customerFields on Customer {
      id
      user {
        ...User.Model.Fragment.Fields
      }
      session {
        id
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.CustomerFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
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

let fragmentType = "Customer";

let fragmentName = "customerFields";
