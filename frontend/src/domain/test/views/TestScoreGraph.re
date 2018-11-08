open Belt;

type scoreObj = {
  .
  "nameList": array(string),
  "denom": string,
  "count": int,
};

let fullWidth =
  ReactDOMRe.Style.make(
    ~width="100%",
    ~padding="2em",
    ~border="solid 1px black",
    ~borderRadius=".2em",
    (),
  );

let sideBySide =
  ReactDOMRe.Style.make(
    ~width="100%",
    ~display="flex",
    ~justifyContent="flex-start",
    (),
  );

let labelStyle = ReactDOMRe.Style.make(~marginRight="3em", ());

let flexBetweenStyle =
  ReactDOMRe.Style.make(~display="flex", ~justifyContent="space-between", ());

let getStudentScore =
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
               LongAnswer(LongAnswerQuestion.Model.idToTypedId("")),
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
                    |> (answerKey => answerKey.data.score) :
                    0.0
                )
              )
         )
  );

let createStatisticsForStudents =
    (
      normalized,
      students: list(Student.Model.Record.t),
      test: Test.Model.Record.t,
    ) => {
  let studentsScores =
    Belt.List.map(students, student =>
      getStudentScore(normalized, student, test)
    );

  (
    Utils.Stats.getMean(studentsScores),
    Utils.Stats.getStdDeviation(studentsScores),
  );
};

let component = ReasonReact.statelessComponent("TestScoreGraph");

let stringOfFloat0 = value => string_of_float(value) ++ "0";

type dataType = {
  .
  "x": float,
  "y": float,
  "fill": string,
  "width": float,
  "height": float,
  "female": int,
  "name": string,
  "nameList": array(string),
  "denom": string,
  "count": int,
};

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
    let studentStatistics =
      createStatisticsForStudents(normalized, students, test);
    let (mean, stdDevaition) = studentStatistics;
    let studentScoreList =
      Belt.List.map(students, student =>
        (student.data.firstName, getStudentScore(normalized, student, test))
      );

    let isMasteryMode =
      test.local.overviewGraphDisplay == OverviewGraphDisplay.Mastery;

    let zScores =
      Utils.Stats.calculateZScore(studentScoreList, studentStatistics);

    <div style=fullWidth>
      <div style=flexBetweenStyle>
        <h1>
          {
            ReasonReact.string(
              isMasteryMode ? "Mastery View" : "Standard View",
            )
          }
        </h1>
        <div>
          <Button
            onClick={
              () =>
                updateTest(
                  Test.Action.ChangeGraphDisplay(
                    isMasteryMode ?
                      OverviewGraphDisplay.Normal :
                      OverviewGraphDisplay.Mastery,
                  ),
                )
                |> ignore
            }
            theme=CTA>
            {
              ReasonReact.string(
                isMasteryMode ?
                  "Switch To Standard View" : "Switch To Mastery View",
              )
            }
          </Button>
        </div>
      </div>
      {
        isMasteryMode ?
          <Chart data={studentScoreList |> Belt.List.toArray} /> :
          <Chart
            data={zScores |> Belt.List.toArray}
            binValues=[|(-3), (-2), (-1), 0, 1, 2, 3|]
          />
      }
      <div style=sideBySide>
        <div style=labelStyle>
          {ReasonReact.string("Mean: ")}
          {ReasonReact.string(mean |> stringOfFloat0)}
        </div>
        <div style=labelStyle>
          {ReasonReact.string("Standard Deviation: ")}
          {ReasonReact.string(stdDevaition |> stringOfFloat0)}
        </div>
      </div>
    </div>;
  },
};