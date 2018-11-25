module M = [%graphql
  {|
    query Restrictions {
      restrictions {
        edges{
          node{
            ...Restriction.Model.Fragment.RestrictionFields
          }
        }
      }
    }
  |}
];