module GraphFragment = [%graphql
  {|
    fragment customerFields on Customer {
      id
      user {
        ...User.Model.Fragment.Fields
      }
      session {
        id
      }
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.CustomerFields;

let fragmentType = "Customer";