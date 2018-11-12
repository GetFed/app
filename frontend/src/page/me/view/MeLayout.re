let component = ReasonReact.statelessComponent("MeLayout");

let make = _children => {
  ...component,
  render: _self =>
    <Me.Container>
      ...{
           (~me) =>
           /* TODO very very wrong */
             Belt.Option.mapWithDefault(me, <div/>, (me) => {
              <User.Container id=me##id>
               ...{(~user) => <UserLayout user />}
             </User.Container>
             })
             
         }
    </Me.Container>,
};