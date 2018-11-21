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

let make = (_children) => {
  ...component,
  render: _self =>
  <SideMenu>
    <SolidOverOpacity>
      <div className=sideMenuInternalClass>
        <div className=sideMenuInternalLogoClass>
          <FedLogo />
        </div>
        <FedMenuLink text="HOME" selected=true/>
        <FedMenuLink text="MY ACCOUNT" selected=false/>
        <FedMenuLink text="GIFTS" selected=false/>
        <div className=sideMenuInternalSeparatorClass />
        <FedMenuLink text="SUPPORT" selected=false/>
        <FedMenuLink text="SIGN OUT" selected=false/>
        <Accounts>
          ...{(~accountSend, ~userId as authUserId) =>
            <Query.Me.Container userId=authUserId>
              ...{(~me) =>
                Belt.Option.mapWithDefault(me, ReasonReact.string("Me Query Failure"), (me) =>
                  Belt.Option.mapWithDefault(authUserId, <LoginLayout accountSend/>, (userId) =>
                    <Customer.Container id=me##id>
                      ...{(~data as customer) => ReasonReact.string("HELLO im logged in")}
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
};