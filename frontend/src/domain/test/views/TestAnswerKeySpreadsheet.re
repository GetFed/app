open Belt;

let checkStyle = ReactDOMRe.Style.make(~color="green", ~fontSize="2em", ());

let xStyle = ReactDOMRe.Style.make(~color="red", ~fontSize="2em", ());

let chartAreaStyle =
  ReactDOMRe.Style.make(
    ~height="100%",
    ~width="100%",
    ~display="flex",
    ~justifyContent="flex-start",
    (),
  );
let fullWidthStyle = ReactDOMRe.Style.make(~height="100%", ~width="100%", ());

let informationalSectionStyle =
  ReactDOMRe.Style.make(
    ~height="100%",
    ~width="100%",
    ~display="flex",
    ~justifyContent="space-between",
    ~marginBottom="1em",
    (),
  );

let emptyButton =
  ReactDOMRe.Style.make(
    ~backgroundColor="transparent",
    ~border="transparent",
    ~cursor="pointer",
    (),
  );

let chevronStyle = ReactDOMRe.Style.make(~height="2.7em", ~width="2.7em", ());

let infoStyles = ReactDOMRe.Style.make(~width="100%", ~maxWidth="75%", ());

let questionColumnName = "(question)";
let objectiveColumnName = "(objective)";
let facilityColumnName = "(facility)";

let redundantRowStyle =
  ReactDOMRe.Style.make(
    ~backgroundColor=Colors.secondary,
    ~borderBottom="solid 1px white", /* what color should this be? */
    (),
  );
/* duplicate from data grid */
let baseRowStyle =
  ReactDOMRe.Style.make(
    ~backgroundColor="white",
    ~borderBottom="solid 1px " ++ Colors.secondary, /* what color should this be? */
    /*~padding="0.5em",*/
    (),
  );

let fitStyle = isFit =>
  ReactDOMRe.Style.make(~width=isFit ? "fit-content" : "100%", ());

let isReduantRow = studentObj =>
  studentObj
  |> Js.Dict.get(_, "name")
  |> Belt.Option.mapWithDefault(_, false, studentName =>
       studentName == questionColumnName
       || studentName == objectiveColumnName
       || studentName == facilityColumnName
     );

let makeQuestionColumns =
    (
      normalized,
      test: Test.Model.Record.t,
      questions,
      totalScore,
      studentsObjs: list(Js.Dict.t(string)),
      facilityObj,
    )
    : list(DataGrid.column(Js.Dict.t(string))) =>
  [
    (
      {
        _Header: "Name",
        accessor: String("name"),
        id: None,
        _Cell: None,
        minWidth: Some(100),
        maxWidth: Some(100),
        headerClassName: None,
      }:
        DataGrid.column(Js.Dict.t(string))
    ),
    (
      {
        _Header: "Score of " ++ string_of_float(totalScore),
        accessor: String("score"),
        id: None,
        _Cell: None,
        minWidth: Some(100),
        maxWidth: Some(100),
        headerClassName: None,
      }:
        DataGrid.column(Js.Dict.t(string))
    ),
    (
      {
        _Header: "%",
        accessor: String("%"),
        id: None,
        _Cell: None,
        minWidth: Some(70),
        maxWidth: Some(70),
        headerClassName: None,
      }:
        DataGrid.column(Js.Dict.t(string))
    ),
  ]
  @ (
    test.local.questionTab != QuestionTab.Overview ?
      questions
      |> Belt.List.mapWithIndex(
           _,
           (_, question: Question.Model.Record.t) => {
             let questionBaseId =
               switch (question) {
               | LongAnswerQuestion(question) => question.data.questionBaseId
               | MultipleChoiceQuestion(question) =>
                 question.data.questionBaseId
               };
             let questionBase =
               normalized
               |> MyNormalizr.Converter.QuestionBase.Remote.getRecord(
                    _,
                    questionBaseId,
                  )
               |> Belt.Option.getWithDefault(
                    _,
                    QuestionBase.Model.Record.defaultWithId(
                      (),
                      questionBaseId,
                    ),
                  );

             questionBase.data.answerKeyIds
             |> Belt.List.map(_, answerKeyId =>
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
                     )
                )
             |> Belt.List.map(
                  _, (answerKey: QuestionAnswerKey.Model.Record.t) =>
                  (
                    {
                      _Header: "",
                      minWidth: Some(66),
                      maxWidth: None,
                      accessor: String(answerKey.data.id),
                      id: None,
                      headerClassName: Some("QuestionNumberHeader"),
                      _Cell:
                        Some(
                          (cellInfo: DataGrid.cellInfo(Js.Dict.t(string))) => {
                            let studentObj =
                              studentsObjs
                              |> Belt.List.get(_, cellInfo##index)
                              |> Belt.Option.getWithDefault(
                                   _,
                                   Js.Dict.empty(),
                                 );

                            let isQuestionRow =
                              studentObj
                              |> Js.Dict.get(_, "name")
                              |> Belt.Option.mapWithDefault(
                                   _, false, studentName =>
                                   studentName == questionColumnName
                                 );

                            studentObj
                            |> Js.Dict.get(_, answerKey.data.id)
                            |> Belt.Option.getWithDefault(_, "false")
                            |> (
                              stringResult =>
                                switch (stringResult) {
                                | "true" => <CheckIcon style=checkStyle />
                                | "false" => <TimesIcon style=xStyle />
                                | a =>
                                  isQuestionRow ?
                                    <TestTooltip
                                      key={answerKey.data.id}
                                      testNumber={a |> int_of_string}
                                      testText={
                                        studentObj
                                        |> Js.Dict.get(
                                             _,
                                             answerKey.data.id ++ "_text",
                                           )
                                        |> Belt.Option.getWithDefault(_, "")
                                      }
                                      maxTextLength=0
                                    /> :
                                    ReasonReact.string(a)
                                }
                            );
                          },
                        ),
                    }:
                      DataGrid.column(Js.Dict.t(string))
                  )
                );
           },
         )
      |> Belt.List.flatten
      |> (
        columnList =>
          test.local.questionTab == QuestionTab.Guttman ?
            Belt.List.sort(columnList, (a, b) =>
              switch (a.accessor, b.accessor) {
              | (String(answerKeyIdA), String(answerKeyIdB)) =>
                switch (
                  Js.Dict.get(facilityObj, answerKeyIdA),
                  Js.Dict.get(facilityObj, answerKeyIdB),
                ) {
                | (Some(facilityValA), Some(facilityValB)) =>
                  facilityValB
                  |> float_of_string > (facilityValA |> float_of_string) ?
                    1 : (-1)
                | _ => (-10000)
                }
              | _ => (-10000)
              }
            ) :
            columnList
      ) :
      []
  );

let totalScore = (normalized, test: Test.Model.Record.t) =>
  test.data.questionIds
  |> Belt.List.map(_, questionId =>
       normalized
       |> MyNormalizr.getQuestionFromSchema(_, questionId)
       |> Belt.Option.getWithDefault(
            _,
            Question.Model.Record.defaultWithId(questionId),
          )
     )
  |> Belt.List.reduce(
       _,
       0.0,
       (memoQuestionVal, question: Question.Model.Record.t) => {
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

         questionBase.data.answerKeyIds
         |> Belt.List.map(_, answerKeyId =>
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
                 )
            )
         |> Belt.List.reduce(_, memoQuestionVal, (memo, answerKey) =>
              memo +. answerKey.data.score
            );
       },
     );

let studentScore =
    (normalized, student: Student.Model.Record.t, test: Test.Model.Record.t) =>
  student.data.testIds
  |> Belt.List.map(_, studentTestId =>
       normalized
       |> MyNormalizr.Converter.StudentTest.Remote.getRecord(
            _,
            studentTestId,
          )
       |> Belt.Option.getWithDefault(
            _,
            StudentTest.Model.Record.defaultWithId(
              test.data.id,
              studentTestId,
            ),
          )
     )
  |> Belt.List.getBy(_, (studentTest: StudentTest.Model.Record.t) =>
       Schema.getUUIDFromId(studentTest.data.originalId) == test.data.id
     )
  |> Option.getWithDefault(
       _,
       StudentTest.Model.Record.default(test.data.id),
     )
  |> (
    studentTest =>
      Belt.List.map(studentTest.data.questionIds, studentQuestionId =>
        normalized
        |> MyNormalizr.Converter.StudentQuestion.Remote.getRecord(
             _,
             studentQuestionId,
           )
        |> Belt.Option.getWithDefault(
             _,
             StudentQuestion.Model.Record.defaultWithId(
               LongAnswer(LongAnswerQuestion.Model.idToTypedId("")), /* yuck */
               studentQuestionId,
             ),
           )
      )
      |> Belt.List.reduce(_, 0.0, (memo, studentQuestion) =>
           studentQuestion.data.answerKeyIds
           |> Belt.List.map(_, studentAnswerKeyId =>
                normalized
                |> MyNormalizr.Converter.StudentAnswerKey.Remote.getRecord(
                     _,
                     studentAnswerKeyId,
                   )
                |> Belt.Option.getWithDefault(
                     _,
                     StudentAnswerKey.Model.Record.defaultWithId(
                       "",
                       studentAnswerKeyId,
                     ),
                   )
              )
           |> Belt.List.reduce(_, memo, (memo, studentAnswerKey) =>
                memo
                +. (
                  studentAnswerKey.data.correct ?
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
                       )
                    |> (
                      (questionAnswerKey: QuestionAnswerKey.Model.Record.t) =>
                        questionAnswerKey.data.score
                    ) :
                    0.0
                )
              )
         )
      |> string_of_float
  );

let getQuestionAnswersWithQuesitonIndexFromTest =
    (normalized, test: Test.Model.Record.t)
    : list((QuestionAnswerKey.Model.Record.t, string, int)) =>
  test.data.questionIds
  |> Belt.List.map(_, questionId =>
       normalized
       |> MyNormalizr.getQuestionFromSchema(_, questionId)
       |> Belt.Option.getWithDefault(
            _,
            Question.Model.Record.defaultWithId(questionId),
          )
     )
  |> Belt.List.mapWithIndex(
       _,
       (idx, question) => {
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

         Belt.List.map(questionBase.data.answerKeyIds, answerKeyId =>
           normalized
           |> MyNormalizr.Converter.QuestionAnswerKey.Remote.getRecord(
                _,
                answerKeyId,
              )
           |> Belt.Option.getWithDefault(
                _,
                QuestionAnswerKey.Model.Record.defaultWithId(
                  (),
                  questionBaseId,
                ),
              )
           |> (answerKey => (answerKey, questionBase.data.text, idx))
         );
       },
     )
  |> Belt.List.flatten;

let getStudentAnswersWithQuestionIndexFromTest =
    (normalized, student: Student.Model.Record.t, test: Test.Model.Record.t)
    : list((StudentAnswerKey.Model.Record.t, int)) =>
  student.data.testIds
  |> Belt.List.map(_, studentTestId =>
       normalized
       |> MyNormalizr.Converter.StudentTest.Remote.getRecord(
            _,
            studentTestId,
          )
       |> Belt.Option.getWithDefault(
            _,
            StudentTest.Model.Record.defaultWithId(
              test.data.id,
              studentTestId,
            ),
          )
     )
  |> Belt.List.getBy(_, (studentTest: StudentTest.Model.Record.t) =>
       Schema.getUUIDFromId(studentTest.data.originalId) == test.data.id
     )
  |> Option.getWithDefault(
       _,
       StudentTest.Model.Record.default(test.data.id),
     )
  |> (
    studentTest =>
      Belt.List.map(studentTest.data.questionIds, studentQuestionId =>
        normalized
        |> MyNormalizr.Converter.StudentQuestion.Remote.getRecord(
             _,
             studentQuestionId,
           )
        |> Belt.Option.getWithDefault(
             _,
             StudentQuestion.Model.Record.defaultWithId(
               LongAnswer(LongAnswerQuestion.Model.idToTypedId("")), /* bad */
               studentQuestionId,
             ),
           )
      )
      |> Belt.List.mapWithIndex(_, (idx, studentQuestion) =>
           Belt.List.map(studentQuestion.data.answerKeyIds, studentAnswerKeyId =>
             normalized
             |> MyNormalizr.Converter.StudentAnswerKey.Remote.getRecord(
                  _,
                  studentAnswerKeyId,
                )
             |> Belt.Option.getWithDefault(
                  _,
                  StudentAnswerKey.Model.Record.defaultWithId(
                    "",
                    studentAnswerKeyId,
                  ),
                )
             |> (studentAnswerKey => (studentAnswerKey, idx))
           )
         )
      |> Belt.List.flatten
  );

let toStudentTestObjs =
    (
      normalized,
      questionAnswersKeysWithQuestionIndex,
      student: Student.Model.Record.t,
      test: Test.Model.Record.t,
    ) => {
  let studentAnswersWithWithQuestionIndex =
    getStudentAnswersWithQuestionIndexFromTest(normalized, student, test);

  let percentageCorrect =
    Belt.List.reduce(
      studentAnswersWithWithQuestionIndex, 0., (memo, (studentAnswerKey, _)) =>
      memo +. (studentAnswerKey.data.correct ? 1. : 0.)
    )
    /. (
      questionAnswersKeysWithQuestionIndex |> Belt.List.length |> float_of_int
    );

  studentAnswersWithWithQuestionIndex
  |> Belt.List.map(
       _, ((studentAnswerKey: StudentAnswerKey.Model.Record.t, _)) =>
       (
         Schema.getUUIDFromId(studentAnswerKey.data.originalId),
         studentAnswerKey.data.correct ? "true" : "false",
       )
     )
  |> (
    answerTuples =>
      [("name", student.data.firstName), ...answerTuples]
      |> (
        answerTuples =>
          [
            ("score", studentScore(normalized, student, test)),
            ...answerTuples,
          ]
          |> (
            answerTuples =>
              [("%", percentageCorrect |> string_of_float), ...answerTuples]
              |> Js.Dict.fromList
          )
      )
  );
};

let facilityForEachQuestionAnswerKey =
    (studentTestObjList, questionAnswersKeysWithQuestionIndex) =>
  Belt.List.map(
    questionAnswersKeysWithQuestionIndex,
    ((questionKeyAnswer: QuestionAnswerKey.Model.Record.t, _, _)) =>
    (
      questionKeyAnswer.data.id,
      Belt.List.reduce(studentTestObjList, 0., (memo, studentTestObj) =>
        memo
        +. (
          studentTestObj
          |> Js.Dict.get(_, questionKeyAnswer.data.id)
          |> (
            checkString =>
              switch (checkString) {
              | Some("true") => 1.
              | _ => 0.
              }
          )
        )
      )
      /. (studentTestObjList |> Belt.List.length |> float_of_int)
      |> string_of_float,
    )
  );

let component = ReasonReact.statelessComponent("TestAnswerKeySpreadsheet");

let make =
    (
      ~test: Test.Model.Record.t,
      ~students,
      ~normalized,
      ~updateTest,
      _children,
    ) => {
  ...component,
  render: _self => {
    let totalScoreVal = totalScore(normalized, test);
    let questionAnswersKeysWithQuestionIndex =
      getQuestionAnswersWithQuesitonIndexFromTest(normalized, test);
    let studentTestObjList =
      List.map(students, student =>
        toStudentTestObjs(
          normalized,
          questionAnswersKeysWithQuestionIndex,
          student,
          test,
        )
      );
    let guttmanSort = test.local.questionTab == QuestionTab.Guttman;

    let facilityObj =
      facilityForEachQuestionAnswerKey(
        studentTestObjList,
        questionAnswersKeysWithQuestionIndex,
      )
      @ [("name", facilityColumnName), ("score", ""), ("%", "")]
      |> Js.Dict.fromList;

    let studentsObjs =
      [
        (
          questionAnswersKeysWithQuestionIndex
          |> Belt.List.map(
               _,
               (
                 (
                   questionAnswerKey: QuestionAnswerKey.Model.Record.t,
                   questionText,
                   questionIdx,
                 ),
               ) =>
               [
                 (questionAnswerKey.data.id, questionIdx + 1 |> string_of_int),
                 (questionAnswerKey.data.id ++ "_text", questionText),
               ]
             )
          |> Belt.List.flatten
        )
        @ [("name", questionColumnName), ("score", ""), ("%", "")]
        |> Js.Dict.fromList,
      ]
      @ [
        Belt.List.map(
          questionAnswersKeysWithQuestionIndex,
          ((questionAnswerKey: QuestionAnswerKey.Model.Record.t, _, _)) =>
          (
            questionAnswerKey.data.id,
            switch (questionAnswerKey.data.objectiveId) {
            | None => "default"
            | Some(objectiveId) =>
              objectiveId
              |> MyNormalizr.Converter.Objective.Remote.getRecord(
                   normalized,
                   _,
                 )
              |> Belt.Option.mapWithDefault(_, "", objective =>
                   objective.data.text
                 )
            },
          )
        )
        @ [("name", objectiveColumnName), ("score", ""), ("%", "")]
        |> Js.Dict.fromList,
      ]
      @ [facilityObj]
      @ studentTestObjList;

    let sortedStudentObjs =
      test.local.questionTab == QuestionTab.Guttman ?
        Belt.List.sort(studentsObjs, (a, b) =>
          switch (Js.Dict.get(a, "%"), Js.Dict.get(b, "%")) {
          | (Some(stringPercentA), Some(stringPercentB)) =>
            switch (stringPercentA, stringPercentB) {
            | ("", _) => (-100000)
            | (_, "") => (-100000)
            | (a, b) =>
              b |> float_of_string > (a |> float_of_string) ? 1 : (-1)
            }
          | _ => (-100000)
          }
        ) :
        studentsObjs;

    let columns: list(DataGrid.column(Js.Dict.t(string))) =
      test.data.questionIds
      |> Belt.List.map(_, questionId =>
           normalized
           |> MyNormalizr.getQuestionFromSchema(_, questionId)
           |> Belt.Option.getWithDefault(
                _,
                Question.Model.Record.defaultWithId(questionId),
              )
         )
      |> makeQuestionColumns(
           normalized,
           test,
           _,
           totalScoreVal,
           sortedStudentObjs,
           facilityObj,
         );

    <div style=fullWidthStyle>
      <div style=informationalSectionStyle>
        <InfoBox info="Words and words and words and words" style=infoStyles />
        <Button
          onClick={
            _ =>
              updateTest(
                Test.Action.ChangeQuestionTabType(
                  test.local.questionTab == QuestionTab.Guttman ?
                    QuestionTab.Extended : QuestionTab.Guttman,
                ),
              )
              |> ignore
          }
          theme=CTA>
          {
            ReasonReact.string(
              test.local.questionTab == QuestionTab.Guttman ?
                "Turn Off Guttman View" : "Switch To Guttman View",
            )
          }
        </Button>
      </div>
      <div style=chartAreaStyle>
        <DataGrid
          pageSize={List.length(sortedStudentObjs)}
          columns
          dataList=sortedStudentObjs
          sortable={!guttmanSort}
          style={fitStyle(test.local.questionTab == QuestionTab.Overview)}
          getTrGroupPropsFn={
            (_, row) => {
              "style":
                isReduantRow(row##row) ? redundantRowStyle : baseRowStyle,
            }
          }
        />
        <button
          style=emptyButton
          className="noButtonHover"
          onClick={
            _ =>
              updateTest(
                Test.Action.ChangeQuestionTabType(
                  test.local.questionTab == QuestionTab.Overview ?
                    QuestionTab.Extended : QuestionTab.Overview,
                ),
              )
              |> ignore
          }>
          {
            test.local.questionTab == QuestionTab.Overview ?
              <ChevronRightIcon style=chevronStyle /> :
              <ChevronLeftIcon style=chevronStyle />
          }
        </button>
      </div>
    </div>;
  },
};