module GraphFragment = [%graphql
  {|
    fragment menuFields on Menu {
      id
      items{
        edges{
          node{
            ...MenuItem.Model.Fragment.Fields
          }
        }
      }
    }
  |}
];


include GraphFragment;
module Fields = GraphFragment.MenuFields;

let fragmentType = "Menu";