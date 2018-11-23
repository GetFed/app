/* This doesn't really belong here but I'll add it it belongs with queries*/
let component = ReasonReact.statelessComponent("CurrentMenuContainer");

module Container = ApolloQuery.Container(Query_CurrentMenu_GraphQL.M);

let make = (children) => {
  /* TODO passing userId is wrong but im doing it for now*/
  ...component,
  render: _ =>
    <Container query={Query_CurrentMenu_GraphQL.M.make()}>
      ...{(~response) => children(~currentMenu=(response##currentMenu ))}
    </Container>,
};