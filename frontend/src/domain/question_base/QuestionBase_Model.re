type _data = {
  id: UUID.t,
  text: string,
  solution: string,
  autoScore: bool,
  forcedResponse: bool,
  questionType: QuestionType.t,
  stimulusId: option(Schema.stimulusId(Schema.modelIdType)),
  answerKeyIds: list(Schema.questionAnswerKeyId(Schema.modelIdType)),
};

/* not can't put the following into a union and pass around */
module GraphFragment = [%graphql
  {|
    fragment questionBaseFields on QuestionBase {
      id
      text
      solution
      autoScore
      forcedResponse
      stimulusId
      questionType
      stimulus{
        ...Stimulus.Model.Fragment.StimulusFields
      }
      answerKeyIds
      answerKeys{
        ...QuestionAnswerKey.Model.Fragment.QuestionAnswerKeyFields
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.QuestionBaseFields;
};

/* Question Local */
type _local = QuestionBase_Local.Model.Record.t;
type _record = RecordType.t(_data, _local);

type idType = Schema.questionBaseId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `QuestionBaseId(id);
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  module UUIDSeedType = {
    let namespace = id;
  };
  module Rand = UUID.V5Random(UUIDSeedType);

  {
    id,
    text: "",
    solution: "",
    autoScore: false,
    forcedResponse: false,
    stimulusId: None,
    questionType: `LONG_ANSWER,
    answerKeyIds: [`QuestionAnswerKeyId(Rand.generateSeqUUID())] /* need to generate first answer key id */
  };
};

let _defaultRecordId = id: _record => {
  data: _defaultData(id),
  local: QuestionBase_Local.Model.Record.default(id),
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
      text: obj##text,
      solution: obj##solution,
      autoScore: obj##autoScore,
      forcedResponse: obj##forcedResponse,
      questionType: obj##questionType,
      stimulusId:
        obj##stimulus |> Belt.Option.map(_, Stimulus.Model.objectToId),
      answerKeyIds:
        obj##answerKeys
        |> Belt.List.fromArray
        |> Belt.List.map(_, QuestionAnswerKey.Model.objectToId),
    };
  };

  let default = _defaultRecord;
  let defaultWithId = ((), id) =>
    _defaultRecordId(id |> Schema.getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: QuestionBase_Local.Model.Record.default(obj##id),
  };
};

module QuestionBaseContainer =
  ApolloFragment.Container(ApolloClient.ReadFragment, Fragment.Fields);
let fragmentType = "QuestionBase";

let fragmentName = "questionBaseFields";

let getById = (id: idType) =>
  QuestionBaseContainer.get(
    ~fragmentType,
    ~fragmentName,
    ~id=Schema.getUUIDFromId(id),
  );