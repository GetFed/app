type _data = {
  id: UUID.t,
  email: string,
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

module ModelSchema = Schema.User;
type idType = ModelSchema.id;
type rootIdType = ModelUtils.RootModel.id;
let idToRootId = ModelSchema.idToRootId;
let getUUIDFromId = ModelSchema.idToString;
let idToTypedId = (id: UUID.t): idType => ModelSchema.stringToId(id);

module Fragment = User_Fragment;
let fragmentType = Fragment.fragmentType;
let fragmentName = Fragment.Fields.name;
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = () => {
  id: UUID.generateUUID(),
  email: "",
  /* UI */
};

let _defaultRecord = (): _record => {data: _defaultData(), local: ()};

let defaultWithId = id => {
  ..._defaultRecord(),
  data: {
    ..._defaultData(),
    id: getUUIDFromId(id),
  },
};

module Record = {
  type t = _record;
  type defaultParam = unit;
  type defaultFn = (defaultParam, idType) => t;

  module Data = {
    type t = _data;
    let fromObject = (obj: Fragment.Fields.t): t => {
      id: obj##id,
      email: "",
    };
  };
  let default = () => _defaultRecord();
  let defaultWithId = ((), id) => {
    ..._defaultRecord(),
    data: {
      ..._defaultData(),
      id: getUUIDFromId(id),
    },
  };
  let findId = (record : _record) => record.data.id;

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: (),
  };
};
