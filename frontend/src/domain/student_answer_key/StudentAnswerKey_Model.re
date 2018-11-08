type _data = {
  id: string,
  correct: bool,
  originalId: Schema.questionAnswerKeyId(Schema.modelIdType),
};

module GraphFragment = [%graphql
  {|
    fragment studentAnswerKeyFields on StudentAnswerKey {
      id
      correct
      originalId
      original{
        ...QuestionAnswerKey.Model.Fragment.QuestionAnswerKeyFields
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.StudentAnswerKeyFields;
};

type _local = unit;
type _record = RecordType.t(_data, _local);

type idType = Schema.studentAnswerKeyId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `StudentAnswerKeyId(id);
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = (answerKeyId: UUID.t) => {
  id: UUID.generateUUID(),
  correct: false,
  originalId: `QuestionAnswerKeyId(answerKeyId),
};

let _defaultRecord = (answerKeyId: UUID.t): _record => {
  data: _defaultData(answerKeyId),
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
      correct: obj##correct,
      originalId: QuestionAnswerKey.Model.objectToId(obj##original),
    };
  };

  let default = answerKey => _defaultRecord(answerKey);
  let defaultWithId = (answerKey, id): _record => {
    data: {
      ..._defaultData(answerKey),
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
let fragmentType = "StudentAnswerKey";

let fragmentName = "studentAnswerKeyFields";
let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));
let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));