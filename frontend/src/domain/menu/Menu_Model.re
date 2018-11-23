type _data = {
  id: UUID.t,
  itemIds: list(option(Schema.menuItemId(Schema.modelIdType))),
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

type idType = Schema.menuId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `MenuId(id);

module GraphFragment = [%graphql
  {|
    fragment menuFields on Menu {
      id
      items{
        edges{
          node{
            ...MenuItem.Model.Fragment.MenuItemFields
          }
        }
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.MenuFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  itemIds: [],
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
      itemIds:
        obj##items
        |> ModelUtils.getConnectionList(_, MenuItem.Model.objectToId)
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

let fragmentType = "Menu";

let fragmentName = "menuFields";
