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
  mb-16
`)|}];

type menuLink =
  | HOME
  | MENU
  | SUPPORT
  | GIFT
  | MY_ACCOUNT;

let idToMenuLink = (pathIds: PathIds.t) : menuLink =>
  switch(pathIds){
  | {myAccountId: Some(_)} => MY_ACCOUNT
  | {giftsId: Some(_)} => GIFT
  | {supportId: Some(_)} => SUPPORT
  | {menuId: Some(_)} => MENU
  | _ => HOME
  };

let make = (~pathIds, _children) => {
  ...component,
  render: _self => {
    let menuLink = idToMenuLink(pathIds);
    Js.log("menuLink = %j");
    Js.log(menuLink);
    <SideMenu>
      <SolidOverOpacity>
        <div className=sideMenuInternalClass>
          <div className=sideMenuInternalLogoClass>
            <FedLogo />
          </div>
          <FedMenuLink text="HOME" selected=(menuLink == HOME)/>
          <FedMenuLink text="MY ACCOUNT" selected=(menuLink == MY_ACCOUNT)/>
          <FedMenuLink text="GIFTS" selected=(menuLink == GIFT)/>
          <div className=sideMenuInternalSeparatorClass />
          <FedMenuLink text="SUPPORT" selected=(menuLink == SUPPORT)/>
          
          <Accounts>
            ...{(~accountSend, ~userId as authUserId) =>
              <Query.Me.Container userId=authUserId>
                ...{(~me) =>
                  Belt.Option.mapWithDefault(me, ReasonReact.string("Me Query Failure"), (me) =>
                    Belt.Option.mapWithDefault(
                      authUserId,
                      <div>
                        <FedMenuLink text="SIGN IN" selected=(false)/>
                        <LoginLayout accountSend/>
                      </div>,
                      (userId) =>
                        <Customer.Container id=me##id>
                          ...{(~data as customer) =>
                            <div>
                              <FedMenuLink text="SIGN OUT" selected=(false)/>
                              {ReasonReact.string("HELLO im logged in")}
                            </div>
                          }
                        </Customer.Container>
                    )
                  )
                }
              </Query.Me.Container>
            }
          </Accounts>
        </div>
      </SolidOverOpacity>
    </SideMenu>
  }
};