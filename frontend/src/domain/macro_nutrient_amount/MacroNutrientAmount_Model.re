type _data = {
  id: UUID.t,
  amount: float,
  nutrientId: Schema.nutrientId(Schema.modelIdType),
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

type idType = Schema.macroNutrientAmountId(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `MacroNutrientAmountId(id);

module GraphFragment = [%graphql
  {|
    fragment macroNutrientAmountFields on MacroNutrientAmount {
      id
      amount
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
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  amount: 0.,
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

let fragmentType = "MacroNutrientAmount";

let fragmentName = "macroNutrientAmountFields";
