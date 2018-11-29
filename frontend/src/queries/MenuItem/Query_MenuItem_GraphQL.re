module M = [%graphql
  {|
    query MenuItem($id: ID!) {
      menuItem(id: $id) {
        ...MenuItem.Model.Fragment.MenuItemFields
      }
    }
  |}
];