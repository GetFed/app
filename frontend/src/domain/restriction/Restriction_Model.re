type _data = {
  id: UUID.t,
  image: option(string),
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

type idType = Schema.restrictionId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `RestrictionId(id);

module GraphFragment = [%graphql
  {|
    fragment restrictionFields on Restriction {
      id
      image
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.RestrictionFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  image: None,
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
      image: obj##image,
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

let fragmentType = "Restriction";

let fragmentName = "restrictionFields";
