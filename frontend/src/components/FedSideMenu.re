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
  | MY_ACCOUNT;

let idToMenuLink = (pathIds: PathIds.t) : menuLink =>
  switch(pathIds){
  | {myAccountId: Some(_)} => MY_ACCOUNT
  | {giftsId: Some(_)} => GIFT
  | {supportId: Some(_)} => SUPPORT
  | {menuId: Some(_)} => MENU
  | {subscriptionId: Some(_)} => SUBSCRIPTION
  | _ => HOME
  };

let make = (~pathIds, ~accountSend, ~authUserId, ~openModal, _children) => {
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
          {
            authUserId == None
              ? <FedMenuLink text="SUBSCRIBE" selected=(menuLink == SUBSCRIPTION)/>
              : <div/>
          }
          <div className=sideMenuInternalSeparatorClass />
          <FedMenuLink text="SUPPORT" selected=(menuLink == SUPPORT)/>
          <Query.Me.Container userId=authUserId>
            ...{(~me) =>
              Belt.Option.mapWithDefault(me, ReasonReact.string("Me Query Failure"), (me) =>
                Belt.Option.mapWithDefault(authUserId,
                  <div onClick=((_) => openModal())>
                    <FedMenuLink text="SIGN IN" selected=(false)/>
                  </div>
                ,
                  (userId) =>
                    <Customer.Container id=me##id>
                      ...{(~data as customer) =>
                        <div>
                          <div onClick=((_) => accountSend(Accounts.Account(Logout)))>
                            <FedMenuLink text="SIGN OUT" selected=(false)/>
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