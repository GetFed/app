module GraphFragment = [%graphql
  {|
    fragment ingredientBaseSpreadFields on Ingredient {
      id
      name
      restrictions {
        edges {
          node {
            ...Restriction.Model.Fragment.Fields
          }
        }
      }
      nutritionFacts {
        ...NutritionFacts.Model.Fragment.Fields
      }
      attributes {
        edges {
          node {
            ...Attribute.Model.Fragment.Fields
          }
        }
      }
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.IngredientBaseSpreadFields;

let fragmentType = "Ingredient";