type _data = {
  id: UUID.t,
  name: string,
  studentIds: list(Schema.studentId(Schema.modelIdType)),
  testIds: list(Schema.testId(Schema.modelIdType)) /* need classroom test model */
  /* UI */
};

type _local = Classroom_Local.Model.Record.t;

type _record = RecordType.t(_data, _local);
type idType = Schema.classroomId(Schema.modelIdType);

let _defaultData = (id) => {
  id,
  name: "",
  studentIds: [],
  testIds: [],
  /* UI */
};

module GraphFragment = [%graphql
  {|
     fragment classroomFields on Classroom {
       id
       name
       studentIds
       students{
         ...Student.Model.Fragment.StudentFields
       }
       testIds
       tests{
         ...Test.Model.Fragment.TestFields
       }
     }
   |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.ClassroomFields;
};

let _defaultRecordId = (id): _record => {
  data: _defaultData(id),
  local: Classroom_Local.Model.Record.default(id),
};


let _defaultRecord = (): _record => {
  _defaultRecordId(UUID.generateUUID())
};

let idToTypedId = (id: UUID.t): idType => `ClassroomId(id);

let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

module Record = {
  type t = _record;
  type defaultParam = unit;
  type defaultFn = (defaultParam, idType) => t;

  module Data = {
    type t = _data;

    let fromObject = (obj: Fragment.Fields.t): t => {
      id: obj##id,
      name: obj##name,
      studentIds:
        obj##students
        |> Belt.List.fromArray
        |> Belt.List.map(_, Student.Model.objectToId),
      testIds:
        obj##tests
        |> Belt.List.fromArray
        |> Belt.List.map(_, Test.Model.objectToId),
    };
  };
  let default = _defaultRecord;
  let defaultWithId = ((), id) => _defaultRecordId(id |> Schema.getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: Classroom_Local.Model.Record.default(obj##id),
  };
};

module Container =
  ApolloFragment.Container(ApolloClient.ReadFragment, Fragment.Fields);
let fragmentType = "Classroom";

let fragmentName = "classroomFields";

let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));