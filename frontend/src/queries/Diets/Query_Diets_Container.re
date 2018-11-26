/* This doesn't really belong here but I'll add it it belongs with queries*/
let component = ReasonReact.statelessComponent("DietsContainer");

module Container = ApolloQuery.Container(Query_Diets_GraphQL.M);

let make = (~loadingComponent=<div />, children) => {
  /* TODO passing userId is wrong but im doing it for now*/
  ...component,
  render: _ =>
    <Container loadingComponent query={Query_Diets_GraphQL.M.make()}>
      ...{(~response) => children(
        ~diets=(
          response##diets |> ModelUtils.getConnectionList(_, Diet.Model.objectToId))
        )
      }
    </Container>,
};