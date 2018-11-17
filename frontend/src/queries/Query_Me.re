module M = [%graphql
  {|
    query Me($id: ID!, $sessionId: ID!) {
      me(id: $id, sessionId: $sessionId) {
        ...Customer.Model.Fragment.CustomerFields
      }
    }
  |}
];