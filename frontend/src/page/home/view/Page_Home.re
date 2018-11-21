let component = ReasonReact.statelessComponent("PageHome");

let css = Css.css;
let tw = Css.tw;
let backgroundImageClass = [%bs.raw {| css(tw`
  w-full
  h-screen
  bg-cover
`)|}];

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <Menu />
      <div className=(backgroundImageClass ++ " bg-image")>
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
    </div>
};