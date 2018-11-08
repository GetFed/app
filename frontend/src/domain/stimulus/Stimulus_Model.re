type _data = {
  id: UUID.t,
  text: string,
};

type _local = Stimulus_Local.Model.Record.t;
type _record = RecordType.t(_data, _local);

type idType = Schema.stimulusId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `StimulusId(id);

module GraphFragment = [%graphql
  {|
    fragment stimulusFields on Stimulus {
      id
      text
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.StimulusFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {id, text: ""};

let _defaultRecordId = id: _record => {
  data: _defaultData(id),
  local: Stimulus_Local.Model.Record.default(id),
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
    };
  };

  let default = () => _defaultRecord();
  let defaultWithId = ((), id) =>
    _defaultRecordId(id |> Schema.getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: Stimulus_Local.Model.Record.default(obj##id),
  };
};

module Container =
  ApolloFragment.Container(ApolloClient.ReadFragment, Fragment.Fields);
let fragmentType = "Stimulus";

let fragmentName = "stimulusFields";

let getById = id =>
  Container.get(~fragmentType, ~fragmentName, ~id=Schema.getUUIDFromId(id));