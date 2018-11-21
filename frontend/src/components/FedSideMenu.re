let component = ReasonReact.statelessComponent("FedSideMenu");

let css = Css.css;
let tw = Css.tw;

let sideMenuInternalClass = [%bs.raw {| css(tw`
  m-4
`)|}];

let make = (_children) => {
  ...component,
  render: _self =>
  <SideMenu>
    <SolidOverOpacity>
      <div className=sideMenuInternalClass>
      <FedLogo />
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