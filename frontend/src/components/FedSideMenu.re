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
  <FedMenuItem key="signin" selected=(false)>
    <div key="signin-container" onClick=((_) => openModal())>
      {ReasonReact.string("SIGN IN")}
    </div>
  </FedMenuItem>
;

let make = (~pathIds, ~accountSend, ~authUserId, ~openModal, _children) => {
  ...component,
  render: _self => {
    let menuLink = idToMenuLink(pathIds);
    
    <SolidOverOpacity key="solidOver">
      <div key="sideMenuInternal" className=sideMenuInternalClass>
        <div key="logo" className=sideMenuInternalLogoClass>
          <FedLogo />
        </div>
        <FedMenuItem key="signin" selected=(menuLink == HOME)>
          <FedMenuLink href="/" text="HOME" /> 
        </FedMenuItem>
        <FedMenuItem key="menu" selected=(menuLink == MENU)>
          <FedMenuLink href="/menu" text="MENU" /> 
        </FedMenuItem>
        <FedMenuItem key="my-account" selected=(menuLink == MY_ACCOUNT)>
          <FedMenuLink href="/my-account" text="MY ACCOUNT" /> 
        </FedMenuItem>
        <FedMenuItem key="gifts" selected=(menuLink == GIFT)>
          <FedMenuLink href="/gifts" text="GIFTS" /> 
        </FedMenuItem>
        {
          authUserId == None
            ? <FedMenuItem key="subscribe" selected=(menuLink == SUBSCRIPTION)>
                <FedMenuLink href="/subscribe" text="SUBSCRIBE" /> 
              </FedMenuItem>
            : <div key="none" />
        }
        <div key="separator" className=sideMenuInternalSeparatorClass />
        <FedMenuItem key="about-us" selected=(menuLink == ABOUT_US)>
          <FedMenuLink href="/about-us" text="ABOUT US" /> 
        </FedMenuItem>

        <FedMenuItem key="support" selected=(menuLink == SUPPORT)>
          <FedMenuLink href="/support" text="SUPPORT" /> 
        </FedMenuItem>
        <Query.Me.Container key="me-container" userId=authUserId loadingComponent=fedSigninLink(openModal)>
          ...{(~me) =>
            Belt.Option.mapWithDefault(me, ReasonReact.string("Me Query Failure"), (me) =>
              Belt.Option.mapWithDefault(authUserId, fedSigninLink(openModal),
                (userId) =>
                  <Customer.Container id=me##id>
                    ...{(~data as customer) =>
                      <div key="container">
                        <FedMenuItem key="signout" selected=(false)>
                          <div key="signout-container" onClick=((_) => accountSend(Accounts.Account(Logout)))>
                            {ReasonReact.string("SIGN OUT")}
                          </div>
                        </FedMenuItem>
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
  }
};