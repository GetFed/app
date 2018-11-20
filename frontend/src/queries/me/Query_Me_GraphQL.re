module M = [%graphql
  {|
    query Me($id: ID!, $sessionId: ID!, $userId: ID) {
      me(id: $id, sessionId: $sessionId, userId: $userId) {
        ...Customer.Model.Fragment.CustomerFields
      }
    }
  |}
];