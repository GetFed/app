module GraphFragment = [%graphql
  {|
    fragment restrictionFields on Restriction {
      id
      name
      image
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.RestrictionFields;

let fragmentType = "Restriction";