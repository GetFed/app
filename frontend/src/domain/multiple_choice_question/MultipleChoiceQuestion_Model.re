type _data = {
  id: UUID.t,
  questionBaseId: Schema.questionBaseId(Schema.modelIdType),
  multipleChoiceId: Schema.multipleChoiceId(Schema.modelIdType),
  /* UI */
};

/* not can't put the following into a union and pass around */
module GraphFragment = [%graphql
  {|
    fragment multipleChoiceQuestionFields on MultipleChoiceQuestion {
      id
      questionBaseId
      questionBase{
        ...QuestionBase.Model.Fragment.QuestionBaseFields
      }
      multipleChoice{
        ...MultipleChoice.Model.Fragment.MultipleChoiceFields
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.MultipleChoiceQuestionFields;
};

type _local = unit;
type _record = RecordType.t(_data, unit);

type idType = Schema.multipleChoiceQuestionId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `MultipleChoiceQuestionId(id);
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id,
  questionBaseId: `QuestionBaseId(id),
  multipleChoiceId: `MultipleChoiceId(UUID.generateUUID()),
};

let _defaultRecord = id: _record => {
  data: _defaultData(id |> Schema.getUUIDFromId),
  local: (),
};

module Record = {
  type t = _record;
  type defaultParam = unit;
  type defaultFn = (defaultParam, idType) => t;
  module Data = {
    type t = _data;
    let fromObject = (obj: Fragment.Fields.t): t => {
      id: obj##id,
      questionBaseId: QuestionBase.Model.objectToId(obj##questionBase),
      multipleChoiceId: MultipleChoice.Model.objectToId(obj##multipleChoice),
    };
  };

  let default = id => _defaultRecord(id);
  let defaultWithId = ((), id: Schema.modelIdType): _record => {
    ..._defaultRecord(id),
    data: {
      ..._defaultData(Schema.getUUIDFromId(id)),
      id: Schema.getUUIDFromId(id),
    },
  };

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: (),
  };
};

module MultipleChoiceQuestionContainer =
  ApolloFragment.Container(ApolloClient.ReadFragment, Fragment.Fields);
let fragmentType = "MultipleChoiceQuestion";

let fragmentName = "multipleChoiceQuestionFields";

let getById = id =>
  MultipleChoiceQuestionContainer.get(
    ~fragmentType,
    ~fragmentName,
    ~id=Schema.getUUIDFromId(id),
  );