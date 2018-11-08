type _data = {
  id: UUID.t,
  testIds: list(Schema.testId(Schema.modelIdType)),
  classroomIds: list(Schema.classroomId(Schema.modelIdType)),
  /* UI */
};

type _local = Teacher_Local.Model.Record.t;
type _record = RecordType.t(_data, _local);

type idType = Schema.teacherId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `TeacherId(id);

module GraphFragment = [%graphql
  {|
    fragment teacherFields on Teacher {
      id
      testIds
      tests{
        ...Test.Model.Fragment.TestFields
      }
      classroomIds
      classrooms{
        ...Classroom.Model.Fragment.ClassroomFields
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.TeacherFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id,
  testIds: [],
  classroomIds: [],
  /* UI */
};

let _defaultRecordId = id: _record => {
  data: _defaultData(id),
  local: Teacher_Local.Model.Record.default(id),
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
      testIds:
        obj##tests
        |> Belt.List.fromArray
        |> Belt.List.map(_, Test.Model.objectToId),
      classroomIds:
        obj##classrooms
        |> Belt.List.fromArray
        |> Belt.List.map(_, Classroom.Model.objectToId),
    };
  };

  let default = () => _defaultRecord();
  let defaultWithId = ((), id): t =>
    _defaultRecordId(id |> Schema.getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: Teacher_Local.Model.Record.default(obj##id),
  };
};

module Container =
  ApolloFragment.Container(ApolloClient.ReadFragment, Fragment.Fields);
let fragmentType = "Teacher";

let fragmentName = "teacherFields";

let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));