let component = ReasonReact.statelessComponent("QuestionAnswerKeyLayout");

let rowStyle = ReactDOMRe.Style.make(~width="100%", ~margin="0", ());

let make =
    (
      ~studentAnswerKey: StudentAnswerKey.Model.Record.t,
      ~normalized,
      ~updateNormalizr:
         Js.Promise.t(MyNormalizr.normalizedType) => Js.Promise.t('a),
      ~updateNormalizedWithReducer,
      _children,
    ) => {
  ...component,
  render: _self => {
    let answerKey =
      normalized
      |> MyNormalizr.Converter.QuestionAnswerKey.Remote.getRecord(
           _,
           studentAnswerKey.data.originalId,
         )
      |> Belt.Option.getWithDefault(
           _,
           QuestionAnswerKey.Model.Record.defaultWithId(
             (),
             studentAnswerKey.data.originalId,
           ),
         );

    <Row style=rowStyle>
      <Col xs=2>
        {answerKey.data.score |> string_of_float |> ReasonReact.string}
      </Col>
      <Col xs=6>
        {
          answerKey.data.objectiveId
          |> Belt.Option.mapWithDefault(_, "default", objectiveId =>
               normalized
               |> MyNormalizr.Converter.Objective.Remote.getRecord(
                    _,
                    objectiveId,
                  )
               |> Belt.Option.mapWithDefault(_, "default", objective =>
                    objective.data.text
                  )
             )
          |> ReasonReact.string
        }
      </Col>
      <Col xs=4>
        {
          let updateStudentAnswerKey = action =>
            normalized
            |> Js.Promise.resolve
            |> updateNormalizedWithReducer
            |> MyNormalizr.Converter.StudentAnswerKey.Remote.updateWithDefault(
                 answerKey.data.id,
                 _,
                 `StudentAnswerKeyId(studentAnswerKey.data.id),
                 action,
               )
            |> updateNormalizr;

          <StudentAnswerKey.Mutation.UpdateStudentAnswerKey>
            ...{
                 (~mutation) =>
                   <Checkbox
                     value={studentAnswerKey.data.correct}
                     onToggle={
                       () =>
                         updateStudentAnswerKey(
                           StudentAnswerKey.Action.ApolloStudentAnswerKey(
                             () =>
                               mutation(
                                 ~id=studentAnswerKey.data.id,
                                 ~correct=!studentAnswerKey.data.correct,
                               ),
                           ),
                         )
                     }
                   />
               }
          </StudentAnswerKey.Mutation.UpdateStudentAnswerKey>;
        }
      </Col>
    </Row>;
  },
};