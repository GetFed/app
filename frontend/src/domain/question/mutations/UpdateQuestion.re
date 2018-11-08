module UpdateQuestion = [%graphql
  {|
    mutation updateQuestion($id: ID!, $text: String!, $solution: String!, $autoScore: Boolean!, $forcedResponse: Boolean!) {
      updateQuestion(question: {id: $id, text: $text, solution: $solution, autoScore: $autoScore, forcedResponse: $forcedResponse}){
        ...on LongAnswerQuestion {
          ...LongAnswerQuestion.Model.Fragment.LongAnswerQuestionFields
        }
        ...on MultipleChoiceQuestion {
          ...MultipleChoiceQuestion.Model.Fragment.MultipleChoiceQuestionFields
        }
      }
    }
  |}
];

let component = ReasonReact.statelessComponent("UpdateQuestion");

module UpdateQuestionMutation = ReasonApollo.CreateMutation(UpdateQuestion);

let make = children => {
  ...component,
  render: _ =>
    <UpdateQuestionMutation>
      ...{
           (mutation, _ /* Result of your mutation */) =>
             children(
               ~mutation=(~id, ~text, ~solution, ~autoScore, ~forcedResponse) => {
               let updateQuestion =
                 UpdateQuestion.make(
                   ~id,
                   ~text,
                   ~solution,
                   ~autoScore,
                   ~forcedResponse,
                   (),
                 );
               mutation(
                 ~variables=updateQuestion##variables,
                 /* ~refetchQueries=[|"member"|], */
                 (),
               );
             })
         }
    </UpdateQuestionMutation>,
};