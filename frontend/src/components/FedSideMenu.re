let component = ReasonReact.statelessComponent("FedSideMenu");

let css = Css.css;
let tw = Css.tw;

let sideMenuInternalClass = [%bs.raw {| css(tw`
  m-8
`)|}];

let sideMenuInternalLogoClass = [%bs.raw {| css(tw`
  mb-4
`)|}];

let sideMenuInternalSeparatorClass = [%bs.raw {| css(tw`
  mb-12
`)|}];

type menuLink =
  | HOME
  | MENU
  | SUPPORT
  | GIFT
  | SUBSCRIPTION
  | ABOUT_US
  | MY_ACCOUNT;

let idToMenuLink = (pathIds: PathIds.t) : menuLink =>
  switch(pathIds){
  | {myAccountId: Some(_)} => MY_ACCOUNT
  | {giftsId: Some(_)} => GIFT
  | {supportId: Some(_)} => SUPPORT
  | {menuId: Some(_)} => MENU
  | {subscriptionId: Some(_)} => SUBSCRIPTION
  | {aboutUsId: Some(_)} => ABOUT_US
  | _ => HOME
  };

let fedSigninLink = (openModal) =>
  <div key="signin-container" onClick=((_) => openModal())>
    <FedMenuLink key="signin" text="SIGN IN" selected=(false)/>
  </div>;

let make = (~pathIds, ~accountSend, ~authUserId, ~openModal, _children) => {
  ...component,
  render: _self => {
    let menuLink = idToMenuLink(pathIds);
    Js.log("menuLink = %j");
    Js.log(menuLink);
    Js.log("HOME");
    Js.log(HOME);

    Js.log("pathIds = %j");
    Js.log(pathIds);
    
    <SideMenu>
      <SolidOverOpacity key="solidOver">
        <div key="sideMenuInternal" className=sideMenuInternalClass>
          <div key="logo" className=sideMenuInternalLogoClass>
            <FedLogo />
          </div>
          <A key="home" href="/">
            <FedMenuLink key="link" text="HOME" selected=(menuLink == HOME)/>
          </A>
          <A key="menu" href="/menu">
            <FedMenuLink key="link" text="MENU" selected=(menuLink == MENU)/>
          </A>
          <A key="my-account" href="/my-account">
            <FedMenuLink key="link" text="MY ACCOUNT" selected=(menuLink == MY_ACCOUNT)/>
          </A>
          <A key="gifts" href="/gifts">
            <FedMenuLink key="link" text="GIFTS" selected=(menuLink == GIFT)/>
          </A>
          {
            authUserId == None
              ? <A key="subscribe" href="/subscribe">
                  <FedMenuLink key="link" text="SUBSCRIBE" selected=(menuLink == SUBSCRIPTION)/>
                </A>
              : <div key="none" />
          }
          <div key="separator" className=sideMenuInternalSeparatorClass />
          <A key="about-us" href="/about-us">
            <FedMenuLink key="link" text="ABOUT US" selected=(menuLink == ABOUT_US)/>
          </A>
          <A key="support" href="/support">
            <FedMenuLink key="link" text="SUPPORT" selected=(menuLink == SUPPORT)/>
          </A>
          <Query.Me.Container key="me-container" userId=authUserId loadingComponent=fedSigninLink(openModal)>
            ...{(~me) =>
              Belt.Option.mapWithDefault(me, ReasonReact.string("Me Query Failure"), (me) =>
                Belt.Option.mapWithDefault(authUserId, fedSigninLink(openModal),
                  (userId) =>
                    <Customer.Container id=me##id>
                      ...{(~data as customer) =>
                        <div key="container">
                          <div key="signout-container" onClick=((_) => accountSend(Accounts.Account(Logout)))>
                            <FedMenuLink key="signout" text="SIGN OUT" selected=(false)/>
                          </div>
                          {ReasonReact.string("HELLO im logged in")}
                        </div>
                      }
                    </Customer.Container>
                )
              )
            }
          </Query.Me.Container>
        </div>
      </SolidOverOpacity>
    </SideMenu>
  }
};