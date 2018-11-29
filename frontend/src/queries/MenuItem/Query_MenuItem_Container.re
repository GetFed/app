/* This doesn't really belong here but I'll add it it belongs with queries*/
let component = ReasonReact.statelessComponent("MenuItemContainer");

module Container = ApolloQuery.Container(Query_MenuItem_GraphQL.M);

let make = (~id, children) => {
  /* TODO passing userId is wrong but im doing it for now*/
  ...component,
  render: _ =>
    <Container query={Query_MenuItem_GraphQL.M.make(~id=id, ())}>
      ...{(~response) => children(~menuItem=(response##menuItem ))}
    </Container>,
};