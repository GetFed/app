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


include GraphFragment;
module Fields = GraphFragment.MineralNutrientAmountFields;

let fragmentType = "MineralNutrientAmount";