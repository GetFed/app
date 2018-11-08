open Belt;

type histogramWithBool = list((string, bool, int));

type questionDetailsObj = {
  .
  "questionNumber": string,
  "questionObjective": string,
  "answerHistogram": histogramWithBool,
  "correctStudents": list(string),
  "incorrectStudents": list(string),
};

let defaultDetailsObj = {
  "questionNumber": "",
  "questionObjective": "",
  "answerHistogram": [],
  "correctStudents": [],
  "incorrectStudents": [],
};

let correctAnswerStyle =
  ReactDOMRe.Style.make(~fontSize="1em", ~color=Colors.correct, ());

let incorrectAnswerStyle =
  ReactDOMRe.Style.make(~fontSize="1em", ~color=Colors.incorrect, ());

let infoStyles =
  ReactDOMRe.Style.make(~width="100%", ~marginBottom="1em", ());

let questionColumns =
    (questionDetailsObjs: list(questionDetailsObj))
    : list(DataGrid.column(questionDetailsObj)) => [
  {
    _Header: "% Class Correct",
    accessor: String(""),
    id: None,
    minWidth: None,
    maxWidth: None,
    _Cell:
      Some(
        (cellInfo: DataGrid.cellInfo(Js.Dict.t(string))) => {
          let questionDetail =
            questionDetailsObjs
            |> Belt.List.get(_, cellInfo##index)
            |> Belt.Option.getWithDefault(_, defaultDetailsObj);

          let countList: list(PieChart.freqData) =
            Belt.List.map(
              questionDetail##answerHistogram,
              ((answerText: string, correct, count: int)) =>
              (
                {freq: count |> float_of_int, name: answerText, correct}: PieChart.freqData
              )
            );

          <VxParentSize>
            {parent => <PieChart data=countList width=parent##width />}
          </VxParentSize>;
        },
      ),
    headerClassName: None,
  },
  {
    _Header: "Question",
    accessor: String("questionNumber"),
    id: None,
    minWidth: None,
    maxWidth: Some(200),
    _Cell:
      Some(
        (cellInfo: DataGrid.cellInfo(Js.Dict.t(string))) => {
          let questionDetail =
            questionDetailsObjs
            |> Belt.List.get(_, cellInfo##index)
            |> Belt.Option.getWithDefault(_, defaultDetailsObj);

          <TestTooltip
            key=questionDetail##questionNumber
            testText=questionDetail##questionNumber
            maxTextLength=100
          />;
        },
      ),
    headerClassName: None,
  },
  {
    _Header: "studentPerformance",
    accessor: String("studentPerformance"),
    id: None,
    minWidth: None,
    maxWidth: None,
    _Cell:
      Some(
        (cellInfo: DataGrid.cellInfo(Js.Dict.t(string))) => {
          let questionDetail =
            questionDetailsObjs
            |> Belt.List.get(_, cellInfo##index)
            |> Belt.Option.getWithDefault(_, defaultDetailsObj);

          <div>
            {
              Belt.List.length(questionDetail##correctStudents) != 0 ?
                <StudentMasteryList
                  listName="Correct Students"
                  correct=true
                  studentList=questionDetail##correctStudents
                /> :
                <div />
            }
            {
              Belt.List.length(questionDetail##incorrectStudents) != 0 ?
                <StudentMasteryList
                  listName="Incorrect Students"
                  correct=false
                  studentList=questionDetail##incorrectStudents
                /> :
                <div />
            }
          </div>;
        },
      ),
    headerClassName: None,
  },
  {
    _Header: "objective",
    accessor: String("questionObjective"),
    id: None,
    minWidth: None,
    maxWidth: Some(100),
    _Cell: None,
    headerClassName: None,
  },
];

let getMaybeStudentAnswerKey =
    (
      student: Student.Model.Record.t,
      normalized,
      testId,
      questionId,
      keyAnswerId,
    ) =>
  student.data.testIds
  |> Belt.List.map(_, studentTestId =>
       normalized
       |> MyNormalizr.Converter.StudentTest.Remote.getRecord(
            _,
            studentTestId,
          )
       |> Belt.Option.getWithDefault(
            _,
            StudentTest.Model.Record.defaultWithId(testId, studentTestId),
          )
     )
  |> Belt.List.getBy(_, (studentTest: StudentTest.Model.Record.t) =>
       Schema.getUUIDFromId(studentTest.data.originalId) == testId
     )
  |> Belt.Option.getWithDefault(_, StudentTest.Model.Record.default(testId))
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
               questionId,
               studentQuestionId,
             ),
           )
      )
      |> Belt.List.getBy(_, studentQuestion =>
           studentQuestion.data.originalId == questionId
         )
      |> Belt.Option.mapWithDefault(_, (None, None), studentQuestion =>
           Belt.List.map(studentQuestion.data.answerKeyIds, studentAnswerKeyId =>
             normalized
             |> MyNormalizr.Converter.StudentAnswerKey.Remote.getRecord(
                  _,
                  studentAnswerKeyId,
                )
             |> Belt.Option.getWithDefault(
                  _,
                  StudentAnswerKey.Model.Record.defaultWithId(
                    keyAnswerId,
                    studentAnswerKeyId,
                  ),
                )
           )
           |> Belt.List.getBy(_, studentAnswerKey =>
                Schema.getUUIDFromId(studentAnswerKey.data.originalId)
                == keyAnswerId
              )
           |> (
             maybeStudentAnswerKey => (
               Some(studentQuestion),
               maybeStudentAnswerKey,
             )
           )
         )
  );

let addAnswerToTextCountList = (list, (answer, correct)) => {
  let match = (text, correctVal) => text == answer && correctVal == correct;

  list
  |> Belt.List.getBy(_, ((text, correctVal, _)) => match(text, correctVal))
  |> (
    maybeHistogramValue =>
      switch (maybeHistogramValue) {
      | None => [(answer, correct, 1), ...list]
      | Some(_) =>
        Belt.List.map(list, ((text, correctVal, count)) =>
          (text, correctVal, count + (match(text, correctVal) ? 1 : 0))
        )
      }
  );
};

let createQuestionDetails =
    (
      normalized,
      students: list(Student.Model.Record.t),
      test: Test.Model.Record.t,
    )
    : list(questionDetailsObj) =>
  test.data.questionIds
  |> Belt.List.mapWithIndex(_, (idx, questionId) => (idx, questionId))
  |> Belt.List.map(_, ((idx, questionId)) =>
       normalized
       |> MyNormalizr.getQuestionFromSchema(_, questionId)
       |> Belt.Option.mapWithDefault(
            _,
            [],
            question => {
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

              Belt.List.map(
                questionBase.data.answerKeyIds, questionKeyAnswerId =>
                (
                  idx,
                  question,
                  normalized
                  |> MyNormalizr.Converter.QuestionAnswerKey.Remote.getRecord(
                       _,
                       questionKeyAnswerId,
                     )
                  |> Belt.Option.getWithDefault(
                       _,
                       QuestionAnswerKey.Model.Record.defaultWithId(
                         (),
                         questionKeyAnswerId,
                       ),
                     ),
                )
              );
            },
          )
     )
  |> Belt.List.flatten
  |> Belt.List.map(
       _,
       ((questionIdx, question: Question.Model.Record.t, questionKeyAnswer)) => {
         let questionId =
           switch (question) {
           | LongAnswerQuestion(question) =>
             Schema.LongAnswer(`LongAnswerQuestionId(question.data.id))
           | MultipleChoiceQuestion(question) =>
             Schema.MultipleChoice(
               `MultipleChoiceQuestionId(question.data.id),
             )
           };
         let questionBaseId =
           `QuestionBaseId(questionId |> Schema.getQuestionUUIDFromId);
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
         let studentQuestionAnswerTupleList =
           Belt.List.map(
             students,
             student => {
               let (maybeStudentQuestion, maybeStudentAnswerKey) =
                 getMaybeStudentAnswerKey(
                   student,
                   normalized,
                   test.data.id,
                   questionId,
                   questionKeyAnswer.data.id,
                 );
               let studentQuestionAnswer =
                 Belt.Option.mapWithDefault(
                   maybeStudentQuestion, "(unanswered)", studentQuestion =>
                   studentQuestion.data.answer
                 );
               let studentQuestionCorrect =
                 Belt.Option.mapWithDefault(
                   maybeStudentAnswerKey, false, studentAnswerKey =>
                   studentAnswerKey.data.correct
                 );
               (
                 studentQuestionAnswer,
                 studentQuestionCorrect,
                 student.data.firstName,
                 student.data.lastName,
               );
             },
           );

         let correctStudents =
           studentQuestionAnswerTupleList
           |> Belt.List.keep(_, ((_, studentQuestionCorrect, _, _)) =>
                studentQuestionCorrect
              )
           |> Belt.List.map(_, ((_, _, firstName, lastName)) =>
                firstName ++ " " ++ lastName
              );

         let incorrectStudents =
           studentQuestionAnswerTupleList
           |> Belt.List.keep(_, ((_, studentQuestionCorrect, _, _)) =>
                !studentQuestionCorrect
              )
           |> Belt.List.map(_, ((_, _, firstName, lastName)) =>
                firstName ++ " " ++ lastName
              );

         let answerHistogram =
           studentQuestionAnswerTupleList
           |> Belt.List.reduce(
                _,
                [],
                (memo, (studentQuestionAnswer, studentQuestionCorrect, _, _)) =>
                addAnswerToTextCountList(
                  memo,
                  (studentQuestionAnswer, studentQuestionCorrect),
                )
              )
           |> Belt.List.sort(_, ((_, _, countA), (_, _, countB)) =>
                countB - countA
              );

         {
           "questionNumber":
             ("Q." ++ (questionIdx + 1 |> string_of_int))
             ++ " "
             ++ questionBase.data.text,
           "questionObjective":
             Belt.Option.mapWithDefault(
               questionKeyAnswer.data.objectiveId, "default", objectiveId =>
               normalized
               |> MyNormalizr.Converter.Objective.Remote.getRecord(
                    _,
                    objectiveId,
                  )
               |> Belt.Option.mapWithDefault(_, "default", objective =>
                    objective.data.text
                  )
             ),
           "answerHistogram": answerHistogram,
           "correctStudents": correctStudents,
           "incorrectStudents": incorrectStudents,
         };
       },
     );

let component =
  ReasonReact.statelessComponent("TestQuestionDetailsSpreadsheet");

let make = (~test: Test.Model.Record.t, ~students, ~normalized, _children) => {
  ...component,
  render: _self => {
    let questionDetailsObjs: list(questionDetailsObj) =
      createQuestionDetails(normalized, students, test);

    <div>
      <InfoBox info="Words and words and words and words" style=infoStyles />
      <DataGrid
        pageSize={List.length(questionDetailsObjs)}
        columns={questionColumns(questionDetailsObjs)}
        dataList=questionDetailsObjs
      />
    </div>;
  },
};