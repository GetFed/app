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





let fedSigninLink = (openModal) =>
  <FedMenuItem key="signin" selected=(false)>
    <div key="signin-container" onClick=((_) => openModal())>
      {ReasonReact.string("SIGN IN")}
    </div>
  </FedMenuItem>
;

let make = (~pathIds, ~accountSend, ~authUserId, ~updateMain, _children) => {
  ...component,
  render: _self => {
    let menuLink = MenuLinkType.idToMenuLink(pathIds);
    
    <SolidOverOpacity key="solidOver">
      <div key="sideMenuInternal" className=sideMenuInternalClass>
        <div key="logo" className=sideMenuInternalLogoClass>
          <FedLogo />
        </div>
        <FedMenuItem selected=(menuLink == HOME)>
          <FedMenuLink key="signin" href="/" text=MenuLinkType.menuLinkToText(HOME) /> 
        </FedMenuItem>
        <FedMenuItem selected=(menuLink == MENU)>
          <FedMenuLink key="menu"  href="/menu" text=MenuLinkType.menuLinkToText(MENU) /> 
        </FedMenuItem>
        <FedMenuItem selected=(menuLink == MY_ACCOUNT)>
          <FedMenuLink key="my-account"  href="/my-account" text=MenuLinkType.menuLinkToText(MY_ACCOUNT) /> 
        </FedMenuItem>
        <FedMenuItem selected=(menuLink == GIFT)>
          <FedMenuLink key="gifts" href="/gifts" text=MenuLinkType.menuLinkToText(GIFT) /> 
        </FedMenuItem>
        {
          authUserId == None
            ? <FedMenuItem selected=(menuLink == SUBSCRIPTION)>
                <div key="subscription"  onClick=((_) => updateMain(Page_Actions.OpenSubscribeModal))>
                  {ReasonReact.string(MenuLinkType.menuLinkToText(SUBSCRIPTION))}
                </div>
              </FedMenuItem>
            : <div key="none" />
        }
        <div key="separator" className=sideMenuInternalSeparatorClass />
        <FedMenuItem selected=(menuLink == ABOUT_US)>
          <FedMenuLink key="about-us"  href="/about-us" text=MenuLinkType.menuLinkToText(ABOUT_US) /> 
        </FedMenuItem>

        <FedMenuItem selected=(menuLink == SUPPORT)>
          <FedMenuLink key="support"  href="/support" text=MenuLinkType.menuLinkToText(SUPPORT) /> 
        </FedMenuItem>
        <Query.Me.Container key="me-container" userId=authUserId loadingComponent=fedSigninLink(() => updateMain(Page_Actions.OpenLoginModal))>
          ...{(~me) =>
            Belt.Option.mapWithDefault(me, ReasonReact.string("Me Query Failure"), (me) =>
              Belt.Option.mapWithDefault(authUserId, fedSigninLink(() => updateMain(Page_Actions.OpenLoginModal)),
                (userId) =>
                  <Customer.Container id=me##id>
                    ...{(customer) =>
                      <div key="container">
                        <FedMenuItem selected=(false)>
                          <div key="signout"  onClick=((_) => accountSend(Accounts.Account(Logout)))>
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