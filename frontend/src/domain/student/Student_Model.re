type _data = {
  id: UUID.t,
  firstName: string,
  lastName: string,
  gradeId: UUID.t,
  testIds: list(Schema.studentTestId(Schema.modelIdType)),
};

module GraphFragment = [%graphql
  {|
    fragment studentFields on Student {
      id
      firstName
      lastName
      gradeId
      grade{
        id
      }
      testIds
      tests{
        ...StudentTest.Model.Fragment.StudentTestFields
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.StudentFields;
};

type _local = Student_Local.Model.Record.t;
type _record = RecordType.t(_data, _local);

type idType = Schema.studentId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `StudentId(id);
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id,
  firstName: "",
  lastName: "",
  gradeId: "",
  testIds: [],
};

let _defaultRecordId = id: _record => {
  data: _defaultData(id),
  local: Student_Local.Model.Record.default(id),
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
      firstName: obj##firstName,
      lastName: obj##lastName,
      gradeId: obj##gradeId,
      testIds:
        obj##tests
        |> Belt.List.fromArray
        |> Belt.List.map(_, StudentTest.Model.objectToId),
    };
  };

  let default = () => _defaultRecord();
  let defaultWithId = ((), id) =>
    _defaultRecordId(id |> Schema.getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: Student_Local.Model.Record.default(obj##id),
  };
};

module Container =
  ApolloFragment.Container(ApolloClient.ReadFragment, Fragment.Fields);
let fragmentType = "Student";

let fragmentName = "studentFields";

let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));