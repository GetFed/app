let component = ReasonReact.statelessComponent("MeLayout");

let make = _children => {
  ...component,
  render: _self =>
    <Accounts>
      ...{(~accountSend, ~userId) => {
        <Me.Container userId>
          ...{(~me) => {
           /* TODO very very wrong */
            Belt.Option.mapWithDefault(me, ReasonReact.string("Me Query Failure"), (me) => {
              Belt.Option.mapWithDefault(userId, <LoginLayout accountSend/>, (userId) => {
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