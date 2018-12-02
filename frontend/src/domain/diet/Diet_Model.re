type _data = {
  id: UUID.t,
  name: string,
  /* UI */
  restrictionIds: option(list(option(Schema.Restriction.idAsType(Schema.modelIdType)))),
};

type _local = unit;
type _record = RecordType.t(_data, _local);

let fragmentType = "Diet";
let fragmentName = "dietFields";
module ModelSchema = Schema.Diet;
type idType = ModelSchema.idAsType(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `DietId(id);

module GraphFragment = [%graphql
  {|
    fragment dietFields on Diet {
      id
      name
      restrictions {
        edges {
          node {
            ...Restriction.Model.Fragment.Fields
          }
        }
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.DietFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  name: "",
  restrictionIds: None,
  /* UI */
};

let _defaultRecordId = id: _record => {
  data: _defaultData(id),
  local: (),
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
      restrictionIds:
        obj##restrictions
        |> Belt.Option.map(_, (res) => ModelUtils.getConnectionList(res, Restriction.Model.objectToId))
    };
  };

  let default = () => _defaultRecord();
  let defaultWithId = ((), id): t =>
    _defaultRecordId(id |> Schema.getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: (),
  };
};


