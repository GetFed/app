module AddStimulus = [%graphql
  {|
    mutation addStimulus($id: ID!, $questionId: ID!) {
      addStimulus(stimulus: {id: $id, questionId: $questionId}){
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

let component = ReasonReact.statelessComponent("AddStimulus");

module AddStimulusMutation = ReasonApollo.CreateMutation(AddStimulus);

let make = children => {
  ...component,
  render: _ =>
    <AddStimulusMutation>
      ...{
           (mutation, _ /* Result of your mutation */) =>
             children(~mutation=(~id, ~questionId) => {
               let addStimulus = AddStimulus.make(~id, ~questionId, ());
               mutation(
                 ~variables=addStimulus##variables,
                 /* ~refetchQueries=[|"member"|], */
                 (),
               );
             })
         }
    </AddStimulusMutation>,
};