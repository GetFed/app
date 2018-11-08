type _data = {
  id: string,
  questionIds: list(Schema.studentQuestionId(Schema.modelIdType)),
  originalId: Schema.testId(Schema.modelIdType),
};

module GraphFragment = [%graphql
  {|
    fragment studentTestFields on StudentTest {
      id
      questionIds
      questions{
        ...StudentQuestion.Model.Fragment.StudentQuestionFields
      }
      originalId
      original{
        ...Test.Model.Fragment.TestFields
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.StudentTestFields;
};

type _local = unit;
type _record = RecordType.t(_data, _local);

type idType = Schema.studentTestId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `StudentTestId(id);
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = (testId: UUID.t) => {
  id: UUID.generateUUID(),
  questionIds: [],
  originalId: `TestId(testId),
};

let _defaultRecord = testId: _record => {
  data: _defaultData(testId),
  local: (),
};

module Record = {
  type t = _record;
  type defaultParam = UUID.t;
  type defaultFn = (defaultParam, idType) => t;

  module Data = {
    type t = _data;
    let fromObject = (obj: Fragment.Fields.t): t => {
      id: obj##id,
      questionIds:
        obj##questions
        |> Belt.List.fromArray
        |> Belt.List.map(_, StudentQuestion.Model.objectToId),
      originalId: Test.Model.objectToId(obj##original),
    };
  };

  let default = _defaultRecord;
  let defaultWithId = (test, id): t => {
    data: {
      ..._defaultData(test),
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
let fragmentType = "StudentTest";

let fragmentName = "studentTestFields";

let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));