type _data = {
  id: string,
  answer: string,
  originalId: Schema.questionId(Schema.modelIdType),
  answerKeyIds: list(Schema.studentAnswerKeyId(Schema.modelIdType)),
  /* UI */
};

module GraphFragment = [%graphql
  {|
    fragment studentQuestionFields on StudentQuestion {
      id
      answer
      originalId
      original {
        ...on LongAnswerQuestion {
          ...LongAnswerQuestion.Model.Fragment.LongAnswerQuestionFields
        }
        ...on MultipleChoiceQuestion {
          ...MultipleChoiceQuestion.Model.Fragment.MultipleChoiceQuestionFields
        }
      }
      answerKeyIds
      answerKeys{
        ...StudentAnswerKey.Model.Fragment.StudentAnswerKeyFields
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.StudentQuestionFields;
};

type _local = unit;
type _record = RecordType.t(_data, _local);

type idType = Schema.studentQuestionId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `StudentQuestionId(id);
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = (questionId: Schema.questionId(Schema.modelIdType)) => {
  id: UUID.generateUUID(),
  answer: "",
  originalId: questionId,
  answerKeyIds: [],
};

let _defaultRecord =
    (questionId: Schema.questionId(Schema.modelIdType)): _record => {
  data: _defaultData(questionId),
  local: (),
};

module Record = {
  type t = _record;
  type defaultParam = Schema.questionId(Schema.modelIdType);
  type defaultFn = (defaultParam, idType) => t;
  module Data = {
    type t = _data;
    let fromObject = (obj: Fragment.Fields.t): t => {
      id: obj##id,
      answer: obj##answer,
      originalId: Question.Model.objectToId(obj##original),
      answerKeyIds:
        obj##answerKeys
        |> Belt.List.fromArray
        |> Belt.List.map(_, StudentAnswerKey.Model.objectToId),
    };
  };
  let default = question => _defaultRecord(question);
  let defaultWithId = (question, id): _record => {
    data: {
      ..._defaultData(question),
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
let fragmentType = "StudentQuestion";

let fragmentName = "studentQuestionFields";

let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));