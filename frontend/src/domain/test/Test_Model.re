type _data = {
  id: UUID.t,
  questionIds: list(Schema.questionId(Schema.modelIdType)),
  objectiveIds: list(option(Schema.objectiveId(Schema.modelIdType))),
  name: string,
  description: string,
  /* UI */
};

module GraphFragment = [%graphql
  {|
     fragment testFields on Test {
       id
       questionIds
       questions {
         ...on LongAnswerQuestion {
           ...LongAnswerQuestion.Model.Fragment.LongAnswerQuestionFields
         }
         ...on MultipleChoiceQuestion {
           ...MultipleChoiceQuestion.Model.Fragment.MultipleChoiceQuestionFields
         }
       }
       objectiveIds
       objectives{
         ...Objective.Model.Fragment.ObjectiveFields
       }
       name
       description
     }
   |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.TestFields;
};

type _local = Test_Local.Model.Record.t;
type _record = RecordType.t(_data, _local);

type idType = Schema.testId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `TestId(id);
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id,
  name: "",
  description: "",
  questionIds: [],
  objectiveIds: [None],
  /* UI */
};

let _defaultRecordId = id: _record => {
  data: _defaultData(id),
  local: Test_Local.Model.Record.default(id),
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
      description: obj##description,
      objectiveIds:
        obj##objectives
        |> Belt.List.fromArray
        |> Belt.List.map(_, obj => Some(Objective.Model.objectToId(obj))),
      questionIds:
        obj##questions
        |> Belt.List.fromArray
        |> Belt.List.map(_, obj => Question.Model.objectToId(obj)),
    };
  };

  let default = () => _defaultRecord();
  let defaultWithId = ((), id) =>
    _defaultRecordId(id |> Schema.getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: Test_Local.Model.Record.default(obj##id),
  };
};

module Container =
  ApolloFragment.Container(ApolloClient.ReadFragment, Fragment.Fields);
let fragmentType = "Test";

let fragmentName = "testFields";

let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));