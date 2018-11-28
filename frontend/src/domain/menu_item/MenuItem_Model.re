type _data = {
  id: UUID.t,
  name: string,
  price: float,
  description: string,
  photo: string,
  restrictionIds: option(list(option(Schema.restrictionId(Schema.modelIdType)))),

  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

type idType = Schema.menuItemId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `MenuId(id);

module GraphFragment = [%graphql
  {|
    fragment menuItemFields on MenuItem {
      id
      name
      description
      price
      photo
      restrictions {
        edges {
          node {
            ...Restriction.Model.Fragment.RestrictionFields
          }
        }
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.MenuItemFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  name: "",
  description: "",
  photo: "",
  price: 0.,
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
      price: obj##price,
      photo: obj##photo,
      description: obj##description,
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

let fragmentType = "MenuItem";

let fragmentName = "menuItemFields";
