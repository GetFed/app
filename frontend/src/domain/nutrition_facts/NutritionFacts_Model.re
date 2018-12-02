type _data = {
  id: UUID.t,
  calories: float,
  servingSize: float,
  servingsPerContainer: float,
  caloriesFromFat: option(float),
  totalFatId: Schema.MacroNutrientAmount.idAsType(Schema.modelIdType),
  transFatId: option(Schema.MacroNutrientAmount.idAsType(Schema.modelIdType)),
  saturatedFatId: Schema.MacroNutrientAmount.idAsType(Schema.modelIdType),
  cholesterolId: Schema.MacroNutrientAmount.idAsType(Schema.modelIdType),
  sodiumId: Schema.MacroNutrientAmount.idAsType(Schema.modelIdType),
  totalCarbohydrateId: Schema.MacroNutrientAmount.idAsType(Schema.modelIdType),
  dietaryFiberId: option(Schema.MacroNutrientAmount.idAsType(Schema.modelIdType)),
  sugarId: Schema.MacroNutrientAmount.idAsType(Schema.modelIdType),
  proteinId: Schema.MacroNutrientAmount.idAsType(Schema.modelIdType),
  mineralIds: list(option(Schema.MineralNutrientAmount.idAsType(Schema.modelIdType))),
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

let fragmentType = "NutritionFacts";
let fragmentName = "nutritionFactsFields";
module ModelSchema = Schema.NutritionFacts;
type idType = ModelSchema.idAsType(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `NutritionFactsId(id);

module GraphFragment = [%graphql
  {|
    fragment nutritionFactsFields on NutritionFacts {
      id
      calories
      servingSize
      servingsPerContainer
      caloriesFromFat
      totalFat{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      transFat{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      saturatedFat{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      cholesterol{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      sodium{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      totalCarbohydrate{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      dietaryFiber{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      sugar{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      protein{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      minerals{
        edges{
          node{
            ...MineralNutrientAmount.Model.Fragment.Fields
          }
        }
      }
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.NutritionFactsFields;
};
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
      proteinId: obj##protein |> MacroNutrientAmount.Model.objectToId,
      mineralIds: obj##minerals |> ModelUtils.getConnectionList(_, MineralNutrientAmount.Model.objectToId),
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


