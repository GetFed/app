type _data = {
  id: UUID.t,
  text: string,
  /* UI */
};

module GraphFragment = [%graphql
  {|
    fragment objectiveFields on Objective {
      id
      text
    }
  |}
];
type idType = Schema.objectiveId(Schema.modelIdType);
let idToTypedId = (id: UUID.t): idType => `ObjectiveId(id);

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.ObjectiveFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

type _local = unit;
type _record = RecordType.t(_data, _local);

let _defaultData = () => {id: UUID.generateUUID(), text: ""};

let _defaultRecord = (): _record => {data: _defaultData(), local: ()};

module Record = {
  type t = _record;
  type defaultParam = unit;
  type defaultFn = (defaultParam, idType) => t;
  module Data = {
    type t = _data;
    let fromObject = (obj: Fragment.Fields.t): t => {
      id: obj##id,
      text: obj##text,
    };
  };

  let default = _defaultRecord;
  let defaultWithId = ((), id): _record => {
    data: {
      ..._defaultData(),
      id: Schema.getUUIDFromId(id),
    },
    local: (),
  };

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: (),
  };
};

module Container =
  ApolloFragment.Container(ApolloClient.ReadFragment, Fragment.Fields);
let fragmentType = "Objective";

let fragmentName = "objectiveFields";

let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));