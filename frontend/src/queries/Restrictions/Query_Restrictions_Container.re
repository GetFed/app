/* This doesn't really belong here but I'll add it it belongs with queries*/
let component = ReasonReact.statelessComponent("RestrictionsContainer");

module Container = ApolloQuery.Container(Query_Restrictions_GraphQL.M);

let make = (~loadingComponent=<div />, children) => {
  /* TODO passing userId is wrong but im doing it for now*/
  ...component,
  render: _ =>
    <Container loadingComponent query={Query_Restrictions_GraphQL.M.make()}>
      ...{
        (~response) => children(
          ~restrictions=(response##restrictions |> ModelUtils.getConnectionList(_, Restriction.Model.objectToId))
        )
      }
    </Container>,
};