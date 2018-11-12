/* This doesn't really belong here but I'll add it it belongs with queries*/
let component = ReasonReact.statelessComponent("MemberContainer");

module Container = ApolloQuery.Container(Query.User.M);

let make = (children) => {
  ...component,
  render: _ =>
    <Container query={Query.User.M.make()}>
      ...{(~response) => children(~me=response##me)}
    </Container>,
};