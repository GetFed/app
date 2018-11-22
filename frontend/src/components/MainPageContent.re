

let component = ReasonReact.statelessComponent("MainPageContent");

let make = (~pathIds: PathIds.t, _children) => {
  ...component,
  render: (_) =>
    switch (pathIds) {
    | {myAccountId: Some(_)} => <MainPageContentMyAccount />
    | {giftsId: Some(_)} => <MainPageContentHome />
    | {supportId: Some(_)} => <MainPageContentHome />
    | {menuId: Some(_)} => <MainPageContentMenu />
    | {subscriptionId: Some(_)} => <MainPageContentHome />
    | {adminId: Some(_)} => <MainPageContentHome />
    | _ => <MainPageContentHome />
    }
};

