/* This doesn't really belong here but I'll add it it belongs with queries*/
let component = ReasonReact.statelessComponent("MeContainer");

module Container = ApolloQuery.Container(Query_Me_GraphQL.M);

let make = (~userId : option(string), ~loadingComponent, children) => {
  /* TODO passing userId is wrong but im doing it for now*/
  ...component,
  render: _ =>
    <Container
      loadingComponent
      query={
        Query_Me_GraphQL.M.make(
          ~id="abc",
          ~sessionId="def",
          ~userId=Belt.Option.getWithDefault(userId, ""),
          ()
        )
    }>
      ...{(~response) => children(~me=(response##me ))}
    </Container>,
};