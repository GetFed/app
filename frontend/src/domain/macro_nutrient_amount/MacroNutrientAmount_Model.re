type _data = {
  id: UUID.t,
  amount: float,
  name: string,
  nutrientId: Schema.Nutrient.idAsType(Schema.modelIdType),
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

let fragmentType = "MacroNutrientAmount";

module ModelSchema = Schema.MacroNutrientAmount;
type idType = ModelSchema.idAsType(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `MacroNutrientAmountId(id);

module GraphFragment = [%graphql
  {|
    fragment macroNutrientAmountFields on MacroNutrientAmount {
      id
      amount
      name
      nutrient {
        ...Nutrient.Model.Fragment.Fields
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.MacroNutrientAmountFields;
};
let fragmentName = Fragment.Fields.name;
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  amount: 0.,
  name: "",
  nutrientId: Nutrient.Model.idToTypedId(""),
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
      amount: obj##amount,
      name: obj##name,
      nutrientId: obj##nutrient |> Nutrient.Model.objectToId,
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


