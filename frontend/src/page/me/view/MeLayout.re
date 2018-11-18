let component = ReasonReact.statelessComponent("MeLayout");

let make = _children => {
  ...component,
  render: _self =>
    <Me.Container>
      ...{
           (~me) => {
           /* TODO very very wrong */

               <Accounts>
                ...{(~accountSend, ~user) => {
                Belt.Option.mapWithDefault(me, <LoginLayout accountSend/>, (me) => {
                    <Customer.Container id=me##id>
                      ...{(~customer) => {
                        <div>
                          <LoginLayout accountSend />
                        </div>
                        }}
                    </Customer.Container>
                  })
                }
                
              }
          </Accounts>
        }
        }
    </Me.Container>,
};