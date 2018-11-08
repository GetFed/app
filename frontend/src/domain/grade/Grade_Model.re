type _data = {
  id: UUID.t,
  name: string,
};

type _local = unit;

type _record = RecordType.t(_data, _local);
type idType = Schema.gradeId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `GradeId(id);

let _defaultData = () => {
  id: UUID.generateUUID(),
  name: "",
  /* UI */
};

module GraphFragment = [%graphql
  {|
     fragment gradeFields on Grade {
       id
       name
     }
   |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.GradeFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultRecord = (): _record => {data: _defaultData(), local: ()};

module Record = {
  type t = _record;
  type defaultParam = unit;
  type defaultFn = (defaultParam, idType) => t;

  module Data = {
    type t = _data;

    let fromObject = (obj: Fragment.Fields.t): t => {
      id: obj##id,
      name: obj##name,
    };
  };
  let default = _defaultRecord;
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

module Container =
  ApolloFragment.Container(ApolloClient.ReadFragment, Fragment.Fields);
let fragmentType = "Grade";

let fragmentName = "gradeFields";

let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));