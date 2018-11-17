let component = ReasonReact.statelessComponent("MeLayout");

let make = _children => {
  ...component,
  render: _self =>
    <Me.Container>
      ...{
           (~me) => {
           /* TODO very very wrong */
           Js.log("me = %j");
               Js.log(me);
               /* Accounts.accountClient; */
             Belt.Option.mapWithDefault(me, <LoginLayout/>, (me) => {
               
              <Customer.Container id=me##id>
               ...{(~customer) => {
                 Js.log("customer = ");
                 Js.log(customer);
                 <div />
                }}
             </Customer.Container>
             })
             }
         }
    </Me.Container>,
};