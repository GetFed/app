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

include GraphFragment;
module Fields = GraphFragment.MacroNutrientAmountFields;

let fragmentType = "MacroNutrientAmount";