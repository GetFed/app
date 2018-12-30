type _data = {
  id: UUID.t,
  calories: float,
  servingSize: float,
  servingsPerContainer: float,
  caloriesFromFat: option(float),
  totalFatId: Schema.MacroNutrientAmount.id,
  transFatId: option(Schema.MacroNutrientAmount.id),
  saturatedFatId: Schema.MacroNutrientAmount.id,
  cholesterolId: Schema.MacroNutrientAmount.id,
  sodiumId: Schema.MacroNutrientAmount.id,
  totalCarbohydrateId: Schema.MacroNutrientAmount.id,
  dietaryFiberId: option(Schema.MacroNutrientAmount.id),
  sugarId: Schema.MacroNutrientAmount.id,
  addedSugarId: Schema.MacroNutrientAmount.id,
  proteinId: Schema.MacroNutrientAmount.id,
  mineralIds: list(option(Schema.MineralNutrientAmount.id)),
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);


module ModelSchema = Schema.NutritionFacts;
type idType = ModelSchema.id;
type rootIdType = ModelUtils.RootModel.id;
let idToRootId = ModelSchema.idToRootId;
let getUUIDFromId = ModelSchema.idToString;
let idToTypedId = (id: UUID.t): idType => ModelSchema.stringToId(id);

module Fragment = NutritionFacts_Fragment;
let fragmentType = Fragment.fragmentType;
let fragmentName = Fragment.Fields.name;
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  calories: 0.,
  servingSize: 0.,
  servingsPerContainer: 0.,
  caloriesFromFat: None,
  totalFatId: MacroNutrientAmount.Model.idToTypedId(id),
  transFatId: None,
  saturatedFatId: MacroNutrientAmount.Model.idToTypedId(id),
  cholesterolId: MacroNutrientAmount.Model.idToTypedId(id),
  sodiumId: MacroNutrientAmount.Model.idToTypedId(id),
  totalCarbohydrateId: MacroNutrientAmount.Model.idToTypedId(id),
  dietaryFiberId: None,
  sugarId: MacroNutrientAmount.Model.idToTypedId(id),
  addedSugarId: MacroNutrientAmount.Model.idToTypedId(id),
  proteinId: MacroNutrientAmount.Model.idToTypedId(id),
  mineralIds: [],
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
      calories: obj##calories,
      servingSize: obj##servingSize,
      servingsPerContainer: obj##servingsPerContainer,
      caloriesFromFat: obj##caloriesFromFat,
      totalFatId: obj##totalFat |> MacroNutrientAmount.Model.objectToId,
      transFatId: obj##transFat |> Belt.Option.map(_, (data) => data |> MacroNutrientAmount.Model.objectToId),
      saturatedFatId: obj##saturatedFat |> MacroNutrientAmount.Model.objectToId,
      cholesterolId: obj##cholesterol |> MacroNutrientAmount.Model.objectToId,
      sodiumId: obj##sodium |> MacroNutrientAmount.Model.objectToId,
      totalCarbohydrateId: obj##totalCarbohydrate |> MacroNutrientAmount.Model.objectToId,
      dietaryFiberId: obj##dietaryFiber |> Belt.Option.map(_, (data) => data |> MacroNutrientAmount.Model.objectToId),
      sugarId: obj##sugar |> MacroNutrientAmount.Model.objectToId,
      addedSugarId: obj##addedSugar |> MacroNutrientAmount.Model.objectToId,
      proteinId: obj##protein |> MacroNutrientAmount.Model.objectToId,
      mineralIds: obj##minerals |> ModelUtils.getConnectionList(_, MineralNutrientAmount.Model.objectToId),
    };
  };

  let default = () => _defaultRecord();
  let defaultWithId = ((), id): t =>
    _defaultRecordId(id |> getUUIDFromId);
  let findId = (record : _record) => record.data.id;

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: (),
  };
};


