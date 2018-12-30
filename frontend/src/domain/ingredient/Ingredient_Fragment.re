module GraphFragment = [%graphql
  {|
    fragment ingredientFields on Ingredient {
      ingredients {
        edges {
          node {
            ...IngredientBaseSpread.Model.Fragment.Fields
          }
        }
      }
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
module Fields = GraphFragment.IngredientFields;

let fragmentType = "Ingredient";