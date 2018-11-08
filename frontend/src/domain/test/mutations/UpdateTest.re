module UpdateTest = [%graphql
  {|
    mutation updateTest($id: ID!, $name: String!, $description: String!) {
      updateTest(test: {id: $id, name: $name, description: $description}){
        ...Test_Model.Fragment.TestFields
      }
    }
  |}
];

let component = ReasonReact.statelessComponent("UpdateTest");

module UpdateTestMutation = ReasonApollo.CreateMutation(UpdateTest);

let make = children => {
  ...component,
  render: _ =>
    <UpdateTestMutation>
      ...{
           (mutation, _ /* Result of your mutation */) =>
             children(~mutation=(~id, ~name, ~description) => {
               let updateTest = UpdateTest.make(~id, ~name, ~description, ());
               mutation(
                 ~variables=updateTest##variables,
                 /* ~refetchQueries=[|"member"|], */
                 (),
               );
             })
         }
    </UpdateTestMutation>,
};