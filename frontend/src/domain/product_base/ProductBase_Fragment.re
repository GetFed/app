module GraphFragment = [%graphql
  {|
    fragment productBaseFields on ProductBase {
      id
      price
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.ProductBaseFields;

let fragmentType = "ProductBase";