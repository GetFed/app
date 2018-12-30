module GraphFragment = [%graphql
  {|
    fragment attributeFields on Attribute {
      id
      name
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.AttributeFields;

let fragmentType = "Attribute";