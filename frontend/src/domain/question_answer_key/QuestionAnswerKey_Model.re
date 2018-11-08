type _data = {
  id: UUID.t,
  score: float,
  objectiveId: option(Schema.objectiveId(Schema.modelIdType)),
  /* UI */
};

module GraphFragment = [%graphql
  {|
    fragment questionAnswerKeyFields on QuestionAnswerKey {
      id
      score
      objectiveId
      objective{
        ...Objective.Model.Fragment.ObjectiveFields
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.QuestionAnswerKeyFields;
};
type _local = QuestionAnswerKey_Local.Model.Record.t;
type _record = RecordType.t(_data, _local);

type idType = Schema.questionAnswerKeyId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `QuestionAnswerKeyId(id);
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultDataId = id => {id, score: 1., objectiveId: None};

let _defaultRecordId = id: _record => {
  data: _defaultDataId(id),
  local: QuestionAnswerKey_Local.Model.Record.default(id),
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
      score: obj##score,
      objectiveId:
        obj##objective |> Belt.Option.map(_, Objective.Model.objectToId),
    };
  };
  let default = () => _defaultRecord();
  let defaultWithId = ((), id) =>
    _defaultRecordId(id |> Schema.getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: QuestionAnswerKey_Local.Model.Record.default(obj##id),
  };
};

module Container =
  ApolloFragment.Container(ApolloClient.ReadFragment, Fragment.Fields);
let fragmentType = "QuestionAnswerKey";

let fragmentName = "questionAnswerKeyFields";

let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));