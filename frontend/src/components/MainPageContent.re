

let component = ReasonReact.statelessComponent("MainPageContent");

let make = (~pathIds: PathIds.t, _children) => {
  ...component,
  render: (_) =>
    switch (pathIds) {
    | {myAccountId: Some(_)} => <MainPageContentMyAccountContainer />
    | {giftsId: Some(_)} => <MainPageContentHomeContainer />
    | {supportId: Some(_)} => <MainPageContentHomeContainer />
    | {menuId: Some(None)} => <MainPageContentMenuContainer />
    | {menuId: Some(Some(menuItemId))} => <MainPageContentMenuItemContainer menuItemId />
    | {subscriptionId: Some(_)} => <MainPageContentHomeContainer />
    | {adminId: Some(_)} => <MainPageContentHomeContainer />
    | _ => <MainPageContentHomeContainer />
    }
};

