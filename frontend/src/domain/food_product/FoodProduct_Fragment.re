module GraphFragment = [%graphql
  {|
    fragment foodProductFields on FoodProduct {
      id
      food{
        ...Ingredient.Model.Fragment.Fields
      }
      product{
        ...ProductBase.Model.Fragment.Fields
      }
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.FoodProductFields;

let fragmentType = "FoodProduct";