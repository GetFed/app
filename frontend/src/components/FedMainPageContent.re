

let component = ReasonReact.statelessComponent("FedMainPageContent");

let make = (~pathIds: PathIds.t, _children) => {
  ...component,
  render: (_) =>
    switch (pathIds) {
    | {myAccountId: Some(_)} => <MainPageContentMyAccount />
    | {giftsId: Some(_)} => <MainPageContentHome />
    | {supportId: Some(_)} => <MainPageContentHome />
    | {menuId: Some(_)} => <MainPageContentHome />
    | {subscriptionId: Some(_)} => <MainPageContentHome />
    | {adminId: Some(_)} => <MainPageContentHome />
    | _ => <MainPageContentHome />
    }
};

