module M = [%graphql
  {|
    query Me {
      me {
        ...User.Model.Fragment.UserFields
      }
    }
  |}
];