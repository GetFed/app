module M = [%graphql
  {|
    query CurrentMenu {
      currentMenu {
        ...Menu.Model.Fragment.MenuFields
      }
    }
  |}
];