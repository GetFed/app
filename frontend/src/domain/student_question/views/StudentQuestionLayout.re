let component = ReasonReact.statelessComponent("StudentQuestionLayout");
let css = Css.css;
let tw = Css.tw;
let fullWidth = ReactDOMRe.Style.make(~width="100%", ());
let studentQuestionLayoutQuestionClass = [%bs.raw {| css(tw` w-full mb-4`)|}];
let questionCardContainerClass = [%bs.raw {| css(tw`  mb-4`)|}];
let flexStartStyle =
  ReactDOMRe.Style.make(
    ~width="100%",
    ~display="flex",
    ~justifyContent="flex-start",
    (),
  );

let questionInfoStyle = ReactDOMRe.Style.make(~paddingRight="1em", ());

let fullSizeFlowStyle =
  ReactDOMRe.Style.make(~height="100%", ~width="100%", ());

let fullSizeStyle = ReactDOMRe.Style.make(~height="95%", ~width="100%", ());

let questionStyle =
  ReactDOMRe.Style.make(~width="100%", ~marginBottom="1em", ());

let checkStyle = ReactDOMRe.Style.make(~color="green", ());

let xStyle = ReactDOMRe.Style.make(~color="red", ());

let checkIfTrue = check =>
  check ? <CheckIcon style=checkStyle /> : <TimesIcon style=xStyle />;

let make =
    (
      ~studentQuestion: StudentQuestion.Model.Record.t,
      ~normalized,
      ~number,
      ~updateNormalizr:
         Js.Promise.t(MyNormalizr.normalizedType) => Js.Promise.t('a),
      ~updateNormalizedWithReducer,
      _children,
    ) => {
  ...component,
  render: _self =>
    switch (
      MyNormalizr.getQuestionFromSchema(
        normalized,
        studentQuestion.data.originalId,
      )
    ) {
    | None => <div />
    | Some(question) =>
      /* this is kind of confusing */
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

      let studentAnswerKeys =
        StudentQuestion_Function.getStudentAnswerKeys(
          normalized,
          question,
          studentQuestion,
        );

      <StudentQuestion.Mutation.GiveAnswerKeyToQuestion>
        ...(
             (~mutation as giveAnswerKeyToQuestionMutation) =>
               <StudentQuestion.Mutation.UpdateStudentQuestion>
                 ...{
                      (~mutation as updateStudentQuestionMutation) => {
                        let studentQuestionAddKeyAnswer =
                          StudentQuestion_Function.createStudentQuestionAddKeyAnswer(
                            question,
                            studentQuestion,
                            giveAnswerKeyToQuestionMutation,
                          );

                        <TestBuilderContentSection
                          sidebar={
                            <div style=fullWidth>
                              <Row>
                                <Col xs=2> {ReasonReact.string("pt")} </Col>
                                <Col xs=6> {ReasonReact.string("obj")} </Col>
                                <Col xs=4>
                                  {ReasonReact.string("correct")}
                                </Col>
                              </Row>
                              {
                                studentAnswerKeys
                                |> Belt.List.map(_, studentAnswerKey =>
                                     <QuestionAnswerKeyLayout
                                       key={studentAnswerKey.data.id}
                                       normalized
                                       updateNormalizr
                                       updateNormalizedWithReducer={
                                         norm =>
                                           norm
                                           |> updateNormalizedWithReducer
                                           |> studentQuestionAddKeyAnswer(
                                                studentAnswerKey,
                                              )
                                       }
                                       studentAnswerKey
                                     />
                                   )
                                |> Utils.ReasonReact.listToReactArray
                              }
                            </div>
                          }>
                          <div className=questionCardContainerClass>
                            <QuestionCard
                              normalized
                              updateNormalizr
                              number
                              question
                              studentQuestion
                              updateNormalizedWithReducer
                            />
                          </div>
                          <div className=studentQuestionLayoutQuestionClass>
                            <Row>
                              <Col xs=2>
                                <h3 className="h3">
                                  {ReasonReact.string("Solution:")}
                                </h3>
                              </Col>
                              <Col xs=10>
                                {
                                  ReasonReact.string(
                                    questionBase.data.solution,
                                  )
                                }
                              </Col>
                            </Row>
                            <div>
                              <LabelContent
                                labelContentList=[
                                  (
                                    "Auto Score",
                                    checkIfTrue(questionBase.data.autoScore),
                                  ),
                                  (
                                    "Forced Response",
                                    checkIfTrue(
                                      questionBase.data.forcedResponse,
                                    ),
                                  ),
                                ]
                              />
                            </div>
                          </div>
                        </TestBuilderContentSection>;
                      }
                    }
               </StudentQuestion.Mutation.UpdateStudentQuestion>
           )
      </StudentQuestion.Mutation.GiveAnswerKeyToQuestion>;
    },
};