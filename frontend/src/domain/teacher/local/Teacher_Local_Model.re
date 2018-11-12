type _record = {
  addingNewClassroom: bool,
};

let _defaultRecord = id => {
  module UUIDSeedType = {
    let namespace = id;
  };
  module Rand = UUID.V5Random(UUIDSeedType);
  {
    addingNewClassroom: false,
  };
};

module Record = {
  type t = _record;
  let default = _defaultRecord;
};