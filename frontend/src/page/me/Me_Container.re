/* This doesn't really belong here but I'll add it it belongs with queries*/
let component = ReasonReact.statelessComponent("MeContainer");

module Container = ApolloQuery.Container(Query.Me.M);

let make = (children) => {
  ...component,
  render: _ =>
    <Container query={Query.Me.M.make(~id="abc", ~sessionId="def", ())}>
      ...{(~response) => {
        Js.log("response = ");
        Js.log(response);
        children(~me=response##me)}
      }
    </Container>,
};