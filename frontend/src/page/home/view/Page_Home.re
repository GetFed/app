let component = ReasonReact.statelessComponent("MeLayout");

let make = _children => {
  ...component,
  render: _self =>
    <Accounts>
      ...{(~accountSend, ~userId as authUserId) =>
        <Query.Me.Container userId=authUserId>
          ...{(~me) =>
            Belt.Option.mapWithDefault(me, ReasonReact.string("Me Query Failure"), (me) =>
              Belt.Option.mapWithDefault(authUserId, <LoginLayout accountSend/>, (userId) =>
                <Customer.Container id=me##id>
                  ...{(~data) => ReasonReact.string("HELLO im logged in")}
                </Customer.Container>
              )
            )
          }
        </Query.Me.Container>
      }
    </Accounts>,
};