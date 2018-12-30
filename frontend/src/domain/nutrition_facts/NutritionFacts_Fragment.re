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
      addedSugar{ ...MacroNutrientAmount.Model.Fragment.MacroNutrientAmountFields }
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


include GraphFragment;
module Fields = GraphFragment.NutritionFactsFields;

let fragmentType = "NutritionFacts";