type _data = {
  id: UUID.t,
  email: string,
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

let fragmentType = "User";
let fragmentName = "userFields";
module ModelSchema = Schema.User;
type idType = ModelSchema.idAsType(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `UserId(id);

module GraphFragment = [%graphql
  {|
    fragment userFields on User {
      id
      createdAt
      defaultAddress {
        id
        firstName
        lastName
        addressLine1
        addressLine2
        addressState
        addressZip{
          id
        }
      }
      amountSpent
      restrictions{
        edges{
          node{
            id
          }
        }
      }
      credit
      phoneNumber
      stripeId
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.UserFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = () => {
  id: UUID.generateUUID(),
  email: "",
  /* UI */
};

let _defaultRecord = (): _record => {data: _defaultData(), local: ()};

let defaultWithId = id => {
  ..._defaultRecord(),
  data: {
    ..._defaultData(),
    id: Schema.getUUIDFromId(id),
  },
};

module Record = {
  type t = _record;
  type defaultParam = unit;
  type defaultFn = (defaultParam, idType) => t;

  module Data = {
    type t = _data;
    let fromObject = (obj: Fragment.Fields.t): t => {
      id: obj##id,
      email: "",
    };
  };
  let default = () => _defaultRecord();
  let defaultWithId = ((), id) => {
    ..._defaultRecord(),
    data: {
      ..._defaultData(),
      id: Schema.getUUIDFromId(id),
    },
  };

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: (),
  };
};
