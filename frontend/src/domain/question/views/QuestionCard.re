let component = ReasonReact.statelessComponent("QuestionCard");
let css = Css.css;
let tw = Css.tw;

let fullWidthClass = [%bs.raw {| css(tw` w-full`)|}];
let studentQuestionLayoutQuestionClass = [%bs.raw {| css(tw` w-full mb-4`)|}];
let studentQuestionLayoutAnswerClass = [%bs.raw {| css(tw` w-full mb-1`)|}];
let flexFullSizeClass = [%bs.raw
  {| css(tw` w-full h-full flex flex-col flex-1 `)|}
];
let fullSizeClass = [%bs.raw {| css(tw` w-full h-full`)|}];

let numberHeaderClass = [%bs.raw
  {| css(tw` w-full text-white bg-blue-lighter pl-2 py-1 flex-no-grow mb-0`)|}
];
let questionContentClass = [%bs.raw
  {| css(tw` px-2 pt-2 border-solid border-blue-lighter border h-full flex-grow `)|}
];

let emptySpaceClass = [%bs.raw {| css(tw` h-64 `)|}];

let questionTextClass = [%bs.raw {| css(tw` w-full font-semibold`)|}];

let make =
    (
      ~normalized,
      ~question: Question.Model.Record.t,
      ~number,
      ~updateNormalizr:
         option(
           Js.Promise.t(MyNormalizr.normalizedType) => Js.Promise.t('a),
         )=?,
      ~updateNormalizedWithReducer=?,
      ~studentQuestion: option(StudentQuestion.Model.Record.t)=?,
      _children,
    ) => {
  ...component,
  render: _self => {
    Js.log("abc");

    let updateNormalizr =
      Belt.Option.getWithDefault(updateNormalizr, _ => Js.Promise.resolve());

    let updateNormalizedWithReducer =
      Belt.Option.getWithDefault(updateNormalizedWithReducer, _ =>
        Js.Promise.resolve(normalized)
      );

    let questionBaseId =
      switch (question) {
      | LongAnswerQuestion(question) => question.data.questionBaseId
      | MultipleChoiceQuestion(question) => question.data.questionBaseId
      };

    let studentQuestionVal =
      Belt.Option.getWithDefault(
        studentQuestion,
        StudentQuestion.Model.Record.default(
          Schema.LongAnswer(
            LongAnswerQuestion.Model.idToTypedId(
              questionBaseId |> Schema.getUUIDFromId,
            ),
          ),
        ),
      );

    let studentAnswerKeys =
      StudentQuestion_Function.getStudentAnswerKeys(
        normalized,
        question,
        studentQuestionVal,
      );

    let questionBase =
      normalized
      |> MyNormalizr.Converter.QuestionBase.Remote.getRecord(
           _,
           questionBaseId,
         )
      |> Belt.Option.getWithDefault(
           _,
           QuestionBase.Model.Record.defaultWithId((), questionBaseId),
         );

    <StudentQuestion.Mutation.GiveAnswerKeyToQuestion>
      ...{
           (~mutation as giveAnswerKeyToQuestionMutation) =>
             <StudentQuestion.Mutation.UpdateStudentQuestion>
               ...{
                    (~mutation as updateStudentQuestionMutation) => {
                      let studentQuestionAddKeyAnswer =
                        StudentQuestion_Function.createStudentQuestionAddKeyAnswer(
                          question,
                          studentQuestionVal,
                          giveAnswerKeyToQuestionMutation,
                        );
                      <StudentAnswerKey.Mutation.UpdateStudentAnswerKey>
                        ...{
                             (~mutation as updateStudentAnswerKey) => {
                               let updateStudentAnswer =
                                 StudentQuestion_Function.createUpdateStudentAnswer(
                                   normalized,
                                   updateNormalizedWithReducer,
                                   updateNormalizr,
                                   question,
                                   studentQuestionVal,
                                   studentAnswerKeys,
                                   studentQuestionAddKeyAnswer,
                                   updateStudentQuestionMutation,
                                   updateStudentAnswerKey,
                                 );

                               <div className=flexFullSizeClass>
                                 <h3 className=numberHeaderClass>
                                   {
                                     "Question "
                                     ++ (number |> string_of_int)
                                     |> ReasonReact.string
                                   }
                                 </h3>
                                 <div className=questionContentClass>
                                   <div className=fullSizeClass>
                                     {
                                       Belt.Option.mapWithDefault(
                                         questionBase.data.stimulusId,
                                         <div key="none" />,
                                         stimulusId => {
                                           let updateStimulus = action =>
                                             MyNormalizr.Converter.Stimulus.Remote.updateWithDefault(
                                               (),
                                               normalized |> Js.Promise.resolve,
                                               stimulusId,
                                               action,
                                             )
                                             |> updateNormalizr;
                                           <div
                                             className=studentQuestionLayoutQuestionClass
                                             key={
                                               stimulusId
                                               |> Schema.getUUIDFromId
                                             }>
                                             <StimulusLayout
                                               stimulusId
                                               normalized /* heres */
                                               editable=false
                                               updateStimulus={
                                                 a => updateStimulus(a)
                                               }
                                             />
                                           </div>;
                                         },
                                       )
                                     }
                                     <div
                                       className=studentQuestionLayoutQuestionClass>
                                       <div className=questionTextClass>
                                         {
                                           questionBase.data.text
                                           |> Utils.String.stringToDivHtml
                                         }
                                       </div>
                                     </div>
                                     {
                                       switch (question) {
                                       | MultipleChoiceQuestion(
                                           multipleChoiceQuestion,
                                         ) =>
                                         let multipleChoiceId =
                                           multipleChoiceQuestion.data.
                                             multipleChoiceId;

                                         <MultipleChoiceLayout
                                           multipleChoiceId
                                           normalized
                                           onSelect=updateStudentAnswer
                                           selectedId={
                                                        studentQuestionVal.data.
                                                          answer
                                                      }
                                         />;
                                       /*
                                        | TrueFalse =>
                                          <MultipleChoiceSelector
                                            selectedId={
                                              studentQuestionVal.data.answer
                                              == "true"
                                            }
                                            selections=[
                                              {id: true, text: "true"},
                                              {id: false, text: "false"},
                                            ]
                                            onSelect=(
                                              selection =>
                                                updateStudentAnswer(
                                                  selection ? "true" : "false",
                                                )
                                            )
                                          />
                                        */
                                       | _ =>
                                         <div
                                           className=studentQuestionLayoutAnswerClass>
                                           {
                                             switch (studentQuestion) {
                                             | Some(studentQuestionVal) =>
                                               <TextArea
                                                 placeholder="Fill in your answer"
                                                 value={
                                                         studentQuestionVal.data.
                                                           answer
                                                       }
                                                 onTextChange=updateStudentAnswer
                                                 autoFocus=false
                                               />
                                             | _ =>
                                               <div
                                                 className=emptySpaceClass
                                               />
                                             }
                                           }
                                         </div>
                                       }
                                     }
                                   </div>
                                 </div>
                               </div>;
                             }
                           }
                      </StudentAnswerKey.Mutation.UpdateStudentAnswerKey>;
                    }
                  }
             </StudentQuestion.Mutation.UpdateStudentQuestion>
         }
    </StudentQuestion.Mutation.GiveAnswerKeyToQuestion>;
  },
};