

let component = ReasonReact.statelessComponent("MainPageContent");

let make = (~pathIds: PathIds.t, _children) => {
  ...component,
  render: (_) =>
    switch (pathIds) {
    | {myAccountId: Some(_)} => <MainPageContentMyAccountContainer />
    | {giftsId: Some(_)} => <MainPageContentHomeContainer />
    | {supportId: Some(_)} => <MainPageContentHomeContainer />
    | {menuId: Some(_)} => <MainPageContentMenuContainer />
    | {subscriptionId: Some(_)} => <MainPageContentHomeContainer />
    | {adminId: Some(_)} => <MainPageContentHomeContainer />
    | _ => <MainPageContentHomeContainer />
    }
};

