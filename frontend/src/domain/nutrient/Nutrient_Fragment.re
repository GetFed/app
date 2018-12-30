module GraphFragment = [%graphql
  {|
    fragment nutrientFields on Nutrient {
      id
      name
      unit
      recommendedDV
    }
  |}
];


include GraphFragment;
module Fields = GraphFragment.NutrientFields;

let fragmentType = "Nutrient";