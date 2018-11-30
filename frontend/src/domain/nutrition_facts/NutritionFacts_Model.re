type _data = {
  id: UUID.t,
  calories: float,
  servingSize: float,
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

type idType = Schema.nutritionFactsId(Schema.modelIdType);

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
      colesterol{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      sodium{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      totalCarbohydrate{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      dietaryFiber{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      sugar{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      protein{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
      minerals{
        edges{
          node{
            ...MineralNutrientAmount.Model.Fragment.MineralNutrientAmountFields
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

let fragmentType = "NutritionFacts";

let fragmentName = "nutritionFactsFields";
