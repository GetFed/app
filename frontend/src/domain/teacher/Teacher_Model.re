type _data = {
  id: UUID.t,
  /* UI */
};

type _local = Teacher_Local.Model.Record.t;
type _record = RecordType.t(_data, _local);

module ModelSchema = Schema.Teacher;
type idType = ModelSchema.idAsType(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `TeacherId(id);

module GraphFragment = [%graphql
  {|
    fragment teacherFields on User {
      id
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.TeacherFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  /* UI */
};

let _defaultRecordId = id: _record => {
  data: _defaultData(id),
  local: Teacher_Local.Model.Record.default(id),
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
    };
  };

  let default = () => _defaultRecord();
  let defaultWithId = ((), id): t =>
    _defaultRecordId(id |> Schema.getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: Teacher_Local.Model.Record.default(obj##id),
  };
};

let fragmentType = "Teacher";

let fragmentName = "teacherFields";
