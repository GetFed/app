let component =
  ReasonReact.statelessComponent("QuestionBuilderObjectiveSection");

let fullWidthStyle = ReactDOMRe.Style.make(~width="100%", ());

let addObjectiveButtonStyle =
  ReactDOMRe.Style.make(~width="100%", ~marginBottom="2em", ());

let fullSizeStyle = ReactDOMRe.Style.make(~height="100%", ~width="100%", ());

let spaceBetweenStyle =
  ReactDOMRe.Style.make(~display="flex", ~justifyContent="space-between", ());

let make =
    (
      ~test: Test.Model.Record.t,
      ~questionId: Schema.questionId(Schema.modelIdType),
      ~normalized,
      ~updateNormalizr:
         Js.Promise.t(MyNormalizr.normalizedType) => Js.Promise.t('a),
      _children,
    ) => {
  ...component,
  render: _self => {
    let question =
      normalized
      |> MyNormalizr.getQuestionFromSchema(_, questionId)
      |> Belt.Option.getWithDefault(
           _,
           Question.Model.Record.defaultWithId(questionId),
         );
    let questionBaseId =
      switch (question) {
      | LongAnswerQuestion(question) => question.data.questionBaseId
      | MultipleChoiceQuestion(question) => question.data.questionBaseId
      };
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

    let updateQuestion = action =>
      MyNormalizr.Converter.QuestionBase.Remote.updateWithDefault(
        (),
        normalized |> Js.Promise.resolve,
        `QuestionBaseId(questionBase.data.id),
        action,
      )
      |> updateNormalizr;

    let updateAnswerKeyId = (id, action) =>
      MyNormalizr.Converter.QuestionAnswerKey.Remote.updateWithDefault(
        (),
        normalized |> Js.Promise.resolve,
        `QuestionAnswerKeyId(id),
        action,
      )
      |> updateNormalizr;

    let onKeyDownScore = id =>
      GenericInput.enterSubmitWithCommand(
        () => updateAnswerKeyId(id, QuestionAnswerKey.Action.ToggleEditScore),
        () => updateAnswerKeyId(id, QuestionAnswerKey.Action.NoOp),
      );

    <div style=fullSizeStyle>
      <Question.Mutation.AddAnswerKey>
        ...{
             (~mutation) =>
               <div style=addObjectiveButtonStyle>
                 <button
                   onClick={
                     _a =>
                       updateQuestion(
                         QuestionBase.Action.ApolloAddAnswerKey(
                           () =>
                             mutation(
                               ~id=
                                 Schema.getUUIDFromId(
                                   questionBase.local.newAnswerKeyId,
                                 ),
                               ~questionId=questionBase.data.id,
                             ),
                         ),
                       )
                       |> ignore
                   }>
                   {ReasonReact.string("+ Objective")}
                 </button>
               </div>
           }
      </Question.Mutation.AddAnswerKey>
      <QuestionAnswerKey.Mutation.UpdateQuestionAnswerKey>
        ...{
             (~mutation) =>
               <div style=fullWidthStyle>
                 {
                   Belt.List.map(
                     questionBase.data.answerKeyIds,
                     answerKeyId => {
                       let answerKey =
                         normalized
                         |> MyNormalizr.Converter.QuestionAnswerKey.Remote.getRecord(
                              _,
                              answerKeyId,
                            )
                         |> Belt.Option.getWithDefault(
                              _,
                              QuestionAnswerKey.Model.Record.defaultWithId(
                                (),
                                answerKeyId,
                              ),
                            );
                       <div
                         style=spaceBetweenStyle
                         key={Schema.getUUIDFromId(answerKeyId)}>
                         <Select
                           key={answerKeyId |> Schema.getUUIDFromId}
                           selectedId={answerKey.data.objectiveId}
                           idToString={
                             objectiveIdMaybe =>
                               switch (objectiveIdMaybe) {
                               | None => "default"
                               | Some(objectiveId) =>
                                 Schema.getUUIDFromId(objectiveId)
                               }
                           }
                           selections={
                             test.data.objectiveIds
                             |> Belt.List.map(
                                  _,
                                  (
                                    objectiveIdMaybe:
                                      option(
                                        Schema.objectiveId(
                                          Schema.modelIdType,
                                        ),
                                      ),
                                  ) =>
                                  (
                                    {
                                      id: objectiveIdMaybe,
                                      text:
                                        Belt.Option.mapWithDefault(
                                          objectiveIdMaybe,
                                          "default",
                                          objectiveId =>
                                          normalized
                                          |> MyNormalizr.Converter.Objective.Remote.getRecord(
                                               _,
                                               objectiveId,
                                             )
                                          |> Belt.Option.mapWithDefault(
                                               _, "default", objective =>
                                               objective.data.text
                                             )
                                        ),
                                    }:
                                      Select.selectionType(
                                        option(
                                          Schema.objectiveId(
                                            Schema.modelIdType,
                                          ),
                                        ),
                                      )
                                  )
                                )
                           }
                           onSelect={
                             a =>
                               updateAnswerKeyId(
                                 answerKey.data.id,
                                 QuestionAnswerKey.Action.ApolloUpdateQuestionAnswer(
                                   () =>
                                     mutation(
                                       ~id=answerKey.data.id,
                                       ~score=answerKey.data.score,
                                       ~objectiveId=
                                         Belt.Option.getWithDefault(a, None),
                                       (),
                                     ),
                                 ),
                               )
                           }
                         />
                         <Editable
                           /* TODO need to give it an intermediat score thing */
                           editing={answerKey.local.editingScore}
                           editingToggle={
                             () =>
                               updateAnswerKeyId(
                                 answerKey.data.id,
                                 QuestionAnswerKey.Action.ToggleEditScore,
                               )
                           }
                           value={answerKey.data.score |> string_of_float}
                           placeholder="1."
                           onTextChange={
                             scoreText =>
                               updateAnswerKeyId(
                                 answerKey.data.id,
                                 QuestionAnswerKey.Action.ApolloUpdateQuestionAnswer(
                                   () =>
                                     mutation(
                                       ~id=answerKey.data.id,
                                       ~score=float_of_string(scoreText),
                                       (),
                                     ),
                                 ),
                               )
                           }
                           onKeyDown={onKeyDownScore(answerKey.data.id)}
                         />
                       </div>;
                     },
                   )
                   |> Utils.ReasonReact.listToReactArray
                 }
               </div>
           }
      </QuestionAnswerKey.Mutation.UpdateQuestionAnswerKey>
    </div>;
  },
};