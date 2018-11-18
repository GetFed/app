let component = ReasonReact.statelessComponent("MeLayout");

let make = _children => {
  ...component,
  render: _self =>
    <Me.Container>
      ...{
           (~me) => {
           /* TODO very very wrong */

               <Accounts>
                ...{(~accountSend, ~userId) => {
                  Js.log("userId");
                    Js.log(userId);
                Belt.Option.mapWithDefault(userId, <LoginLayout accountSend/>, (userId) => {
                    

                    Js.log("me");
                    Js.log(me);

                    <div>
                          <LoginLayout accountSend />
                        </div>


                    /* <Customer.Container id=me##id>
                      ...{(~customer) => {
                        <div>
                          <LoginLayout accountSend />
                        </div>
                        }}
                    </Customer.Container> */
                  })
                }
                
              }
          </Accounts>
        }
        }
    </Me.Container>,
};