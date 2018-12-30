module GraphFragment = [%graphql
  {|
    fragment dietFields on Diet {
      id
      name
      restrictions {
        edges {
          node {
            ...Restriction.Model.Fragment.Fields
          }
        }
      }
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.DietFields;

let fragmentType = "Diet";