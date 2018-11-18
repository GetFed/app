let component = ReasonReact.statelessComponent("MeLayout");

let make = _children => {
  ...component,
  render: _self =>
    <Accounts>
      ...{(~accountSend, ~userId) => {
        <Me.Container>
          ...{(~me) => {
           /* TODO very very wrong */
            Belt.Option.mapWithDefault(me, ReasonReact.string("Me Query Failure"), (me) => {
              Js.log("HELLO me");
              Js.log(me);
              Belt.Option.mapWithDefault(userId, <LoginLayout accountSend/>, (userId) => {
                Js.log("userId");
                Js.log(userId);
                <Customer.Container id=me##id>
                  ...{(~customer) => {
                    Js.log("customer = ");
                    Js.log(customer);
                    <div>
                      {ReasonReact.string("HELLO im logged in")}
                    </div>
                  }}
                </Customer.Container>
              });
            });
          }}
        </Me.Container>
      }}
    </Accounts>,
};