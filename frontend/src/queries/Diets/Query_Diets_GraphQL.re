module M = [%graphql
  {|
    query Diets {
      diets {
        edges{
          node{
            ...Diet.Model.Fragment.DietFields
          }
        }
      }
    }
  |}
];