module GraphFragment = [%graphql
  {|
    fragment userFields on User {
      id
      createdAt
      defaultAddress {
        id
        firstName
        lastName
        addressLine1
        addressLine2
        addressState
        addressZip{
          id
        }
      }
      amountSpent
      restrictions{
        edges{
          node{
            id
          }
        }
      }
      credit
      phoneNumber
      stripeId
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.UserFields;

let fragmentType = "User";