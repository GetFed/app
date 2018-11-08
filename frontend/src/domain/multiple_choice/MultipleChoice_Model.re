type _data = {
  id: UUID.t,
  choices: list(Choice.t),
};

type _local = MultipleChoice_Local.Model.Record.t;
type _record = RecordType.t(_data, _local);

type idType = Schema.multipleChoiceId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `MultipleChoiceId(id);

let _defaultData = (id: UUID.t): _data => {id, choices: []};

module GraphFragment = [%graphql
  {|
    fragment multipleChoiceFields on MultipleChoice {
      id
      choiceIds
      choices {
        id
        text
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.MultipleChoiceFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultRecordId = id: _record => {
  data: _defaultData(id),
  local: MultipleChoice_Local.Model.Record.default(id),
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
      choices:
        obj##choices
        |> Belt.List.fromArray
        |> Belt.List.map(_, obj => ({id: obj##id, text: obj##text}: Choice.t)) /* How do i get these? */,
    };
  };

  let default = _defaultRecord;
  let defaultWithId = ((), id) =>
    _defaultRecordId(id |> Schema.getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: MultipleChoice_Local.Model.Record.default(obj##id),
  };
};

module Container =
  ApolloFragment.Container(ApolloClient.ReadFragment, Fragment.Fields);
let fragmentType = "MultipleChoice";

let fragmentName = "multipleChoiceFields";

let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));