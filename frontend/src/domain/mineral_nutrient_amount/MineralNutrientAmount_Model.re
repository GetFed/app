type _data = {
  id: UUID.t,
  name: string,
  percentageDailyValue: float,
  nutrientId: Schema.Nutrient.idAsType(Schema.modelIdType),
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

module ModelSchema = Schema.MineralNutrientAmount;
type idType = ModelSchema.idAsType(Schema.modelIdType);

let fragmentType = "MineralNutrientAmount";
let fragmentName = "mineralNutrientAmountFields";
let idToTypedId = (id: UUID.t): idType => `MineralNutrientAmountId(id);

module GraphFragment = [%graphql
  {|
    fragment mineralNutrientAmountFields on MineralNutrientAmount {
      id
      name
      percentageDailyValue
      nutrient {
        ...Nutrient.Model.Fragment.Fields
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.MineralNutrientAmountFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  name: "",
  percentageDailyValue: 0.,
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
      name: obj##name,
      percentageDailyValue: obj##percentageDailyValue,
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


