open Belt;

type objectiveDetailsObj = {
  .
  "objective": string,
  "classCorrect": string,
  "questionsWithObjective": list((QuestionBase.Model.Record.t, int)),
  "studentObjectivesCorrectWithStatistics": (
    list((string, float)),
    (float, float),
  ),
};

let defaultObjectiveDetailsObj = {
  "objective": "",
  "classCorrect": "",
  "questionsWithObjective": [],
  "studentObjectivesCorrectWithStatistics": ([], (0., 0.)),
};

let infoStyles =
  ReactDOMRe.Style.make(~width="100%", ~marginBottom="1em", ());

let makeObjectiveColumns =
    objectiveObjs: list(DataGrid.column(objectiveDetailsObj)) => [
  (
    {
      _Header: "Objective",
      accessor: String("objective"),
      id: None,
      minWidth: None,
      maxWidth: Some(200),
      headerClassName: None,
      _Cell:
        Some(
          (cellInfo: DataGrid.cellInfo(objectiveDetailsObj)) => {
            let objectiveObj =
              objectiveObjs
              |> Belt.List.get(_, cellInfo##index)
              |> Belt.Option.getWithDefault(_, defaultObjectiveDetailsObj);

            <div>
              <h3> {ReasonReact.string(objectiveObj##objective)} </h3>
              <div> {ReasonReact.string("Class Correct")} </div>
              <h1> {ReasonReact.string(objectiveObj##classCorrect)} </h1>
            </div>;
          },
        ),
    }:
      DataGrid.column(objectiveDetailsObj)
  ),
  (
    {
      _Header: "Related Questions to Objective",
      accessor: String("questionsWithObjective"),
      id: None,
      _Cell:
        Some(
          (cellInfo: DataGrid.cellInfo(objectiveDetailsObj)) => {
            let objectiveObj =
              objectiveObjs
              |> Belt.List.get(_, cellInfo##index)
              |> Belt.Option.getWithDefault(_, defaultObjectiveDetailsObj);

            let questionsWithIndex = objectiveObj##questionsWithObjective;

            <div>
              {
                questionsWithIndex
                |> Belt.List.map(
                     _, ((questionBase: QuestionBase.Model.Record.t, idx)) =>
                     <TestTooltip
                       key={questionBase.data.id}
                       testText={questionBase.data.text}
                       testNumber=idx
                     />
                   )
                |> Utils.ReasonReact.listToReactArray
              }
            </div>;
          },
        ),
      minWidth: None,
      maxWidth: None,
      headerClassName: None,
    }:
      DataGrid.column(objectiveDetailsObj)
  ),
  (
    {
      _Header: "",
      accessor: String("studentObjectivesCorrectWithStatistics"),
      id: None,
      _Cell:
        Some(
          (cellInfo: DataGrid.cellInfo(objectiveDetailsObj)) => {
            let objectiveObj =
              objectiveObjs
              |> Belt.List.get(_, cellInfo##index)
              |> Belt.Option.getWithDefault(_, defaultObjectiveDetailsObj);

            let (studentObjectivesCorrect, objectiveStatistics) =
              objectiveObj##studentObjectivesCorrectWithStatistics;

            let scoreHistogram =
              Utils.Stats.createScoreDenomHistogram(
                studentObjectivesCorrect,
                objectiveStatistics,
              );

            let lowScores =
              scoreHistogram
              |> Belt.List.getBy(_, ({denom}) => denom == "a Low Scores")
              |> Belt.Option.mapWithDefault(_, [], ({nameList}) => nameList);

            let highScores =
              scoreHistogram
              |> Belt.List.getBy(_, ({denom}) => denom == "d High Scores")
              |> Belt.Option.mapWithDefault(_, [], ({nameList}) => nameList);

            <div>
              <StudentMasteryList
                listName="Masters"
                correct=true
                studentList=highScores
              />
              <StudentMasteryList
                listName="Developing"
                correct=false
                studentList=lowScores
              />
            </div>;
          },
        ),
      minWidth: None,
      maxWidth: None,
      headerClassName: None,
    }:
      DataGrid.column(objectiveDetailsObj)
  ),
];

let calcObjectiveStatistics = (values: list(float)) => (
  Utils.Stats.getMean(values),
  Utils.Stats.getStdDeviation(values),
);

let toObjectiveObj =
    (
      normalized,
      students,
      test: Test.Model.Record.t,
      objective: Objective.Model.Record.t,
    ) => {
  let questionsBaseWithIndex =
    Belt.List.mapWithIndex(
      test.data.questionIds,
      (idx, questionId) => {
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

        (questionBase, idx);
      },
    );

  let questionsWithObjective =
    Belt.List.keep(questionsBaseWithIndex, ((questionBase, _idx)) =>
      questionBase.data.answerKeyIds
      |> Belt.List.map(_, questionAnswerKeyId =>
           normalized
           |> MyNormalizr.Converter.QuestionAnswerKey.Remote.getRecord(
                _,
                questionAnswerKeyId,
              )
           |> Belt.Option.getWithDefault(
                _,
                QuestionAnswerKey.Model.Record.defaultWithId(
                  (),
                  questionAnswerKeyId,
                ),
              )
         )
      |> Belt.List.some(_, answerKey =>
           Belt.Option.mapWithDefault(
             answerKey.data.objectiveId,
             "",
             Schema.getUUIDFromId,
           )
           == objective.data.id
         )
    );
  let answerKeyIds =
    questionsWithObjective
    |> Belt.List.map(_, ((questionBase, _idx)) =>
         questionBase.data.answerKeyIds
       )
    |> Belt.List.flatten
    |> Belt.List.map(_, questionAnswerKeyId =>
         normalized
         |> MyNormalizr.Converter.QuestionAnswerKey.Remote.getRecord(
              _,
              questionAnswerKeyId,
            )
         |> Belt.Option.getWithDefault(
              _,
              QuestionAnswerKey.Model.Record.defaultWithId(
                (),
                questionAnswerKeyId,
              ),
            )
       )
    |> Belt.List.keep(_, answerKey =>
         Belt.Option.mapWithDefault(
           answerKey.data.objectiveId,
           "",
           Schema.getUUIDFromId,
         )
         == objective.data.id
       );

  let studentObjectivesCorrect =
    Belt.List.map(students, (student: Student.Model.Record.t) =>
      (
        student.data.firstName,
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
        |> Belt.List.getBy(_, studentTest =>
             Schema.getUUIDFromId(studentTest.data.originalId) == test.data.id
           )
        |> Belt.Option.getWithDefault(
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
            |> Belt.List.map(_, studentQuestion =>
                 studentQuestion.data.answerKeyIds
               )
            |> Belt.List.flatten
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
            |> Belt.List.keep(_, studentAnswerKey =>
                 studentAnswerKey.data.correct
               )
            |> Belt.List.map(_, studentAnswerKey =>
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
               )
            |> Belt.List.keep(_, answerKey =>
                 Belt.Option.mapWithDefault(
                   answerKey.data.objectiveId,
                   "",
                   Schema.getUUIDFromId,
                 )
                 == objective.data.id
               )
            |> Belt.List.length
            |> float_of_int
        ),
      )
    );

  let objectiveStatistics =
    studentObjectivesCorrect
    |> Belt.List.map(_, ((_name, correct)) => correct)
    |> calcObjectiveStatistics;

  let totalAnswerKeyNum = Belt.List.length(answerKeyIds);

  {
    "objective": objective.data.text,
    "classCorrect":
      studentObjectivesCorrect
      |> Belt.List.reduce(_, 0., (memo, (_name, numberRight)) =>
           numberRight +. memo
         )
      |> (
        totalRight =>
          totalRight
          /. (
            (totalAnswerKeyNum |> float_of_int)
            *. (students |> Belt.List.length |> float_of_int)
          )
          |> (
            totalPercentage =>
              totalPercentage
              *. 100.
              |> Js.Float.toFixedWithPrecision(_, ~digits=2)
              |> (percentage => percentage ++ "%")
          )
      ),
    "questionsWithObjective": questionsWithObjective,
    "studentObjectivesCorrectWithStatistics": (
      studentObjectivesCorrect,
      objectiveStatistics,
    ),
  };
};

let toObjectiveObjs =
    (
      normalized,
      students: list(Student.Model.Record.t),
      test: Test.Model.Record.t,
    )
    : list(objectiveDetailsObj) =>
  test.data.objectiveIds
  |> Utils.List.removeOptionsFromList
  |> Belt.List.map(_, objectiveId =>
       normalized
       |> MyNormalizr.Converter.Objective.Remote.getRecord(_, objectiveId)
       |> Belt.Option.getWithDefault(
            _,
            Objective.Model.Record.defaultWithId((), objectiveId),
          )
     )
  |> Belt.List.map(_, toObjectiveObj(normalized, students, test));

let component = ReasonReact.statelessComponent("TestObjectiveSpreadsheet");

let make = (~test: Test.Model.Record.t, ~students, ~normalized, _children) => {
  ...component,
  render: _self => {
    let objectiveObjs = toObjectiveObjs(normalized, students, test);

    <div>
      <InfoBox info="Words and words and words and words" style=infoStyles />
      <DataGrid
        pageSize={List.length(objectiveObjs)}
        columns={makeObjectiveColumns(objectiveObjs)}
        dataList=objectiveObjs
      />
    </div>;
  },
};