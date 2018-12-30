module GraphFragment = [%graphql
  {|
    fragment menuItemFields on MenuItem {
      id
      name
      description
      photo
      product{
        ...FoodProduct.Model.Fragment.Fields
      }
    }
  |}
];



include GraphFragment;
module Fields = GraphFragment.MenuItemFields;

let fragmentType = "MenuItem";