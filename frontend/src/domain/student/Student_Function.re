let updateClassroomAndStudentNormalizr =
    (
      normalized,
      giveTestToClassroomMutation,
      giveTestToStudent,
      classroom: Classroom.Model.Record.t,
      studentTest: StudentTest.Model.Record.t,
      student: Student.Model.Record.t,
      norm,
    ) => {
  let classroomHasTest =
    classroom.data.testIds
    |> Belt.List.keep(_, testId => testId == studentTest.data.originalId)
    |> Belt.List.length
    |> (res => res != 0);

  let studentHasTest =
    student.data.testIds
    |> MyNormalizr.idListToFilteredItems(
         _,
         MyNormalizr.Converter.StudentTest.Remote.getRecord(normalized),
       )
    |> Belt.List.keep(_, foundStudentTest =>
         foundStudentTest.data.originalId == studentTest.data.originalId
       )
    |> Belt.List.length
    |> (res => res != 0);

  let classroomTestNorm =
    classroomHasTest ?
      norm :
      MyNormalizr.Converter.Classroom.Remote.updateWithDefault(
        (),
        norm,
        `ClassroomId(classroom.data.id),
        ApolloGiveTestToClassroom(
          () =>
            giveTestToClassroomMutation(
              ~testId=studentTest.data.originalId |> Schema.getUUIDFromId,
              ~classroomId=classroom.data.id,
            ),
        ),
      );

  studentHasTest ?
    classroomTestNorm :
    MyNormalizr.Converter.Student.Remote.updateWithDefault(
      (),
      classroomTestNorm,
      `StudentId(student.data.id),
      ApolloGiveTestToStudent(
        () =>
          giveTestToStudent(
            ~id=studentTest.data.id,
            ~originalId=Schema.getUUIDFromId(studentTest.data.originalId),
            ~studentId=student.data.id,
          ),
      ),
    );
};

let createStudentQuestionTestNormalizr =
    (
      updateNormalizedWithReducer,
      test: Test.Model.Record.t,
      studentTest: StudentTest.Model.Record.t,
      giveQuestionToTestMutation,
      studentQuestion: StudentQuestion.Model.Record.t,
      norm,
    ) => {
  let normPromise = norm |> updateNormalizedWithReducer;

  let numQuestionsInList =
    studentTest.data.questionIds
    |> Belt.List.keep(_, questionId =>
         questionId |> Schema.getUUIDFromId == studentQuestion.data.id
       )
    |> Belt.List.length;

  let hasQuestionInList = numQuestionsInList != 0;

  hasQuestionInList ?
    normPromise :
    normPromise
    |> MyNormalizr.Converter.StudentTest.Remote.updateWithDefault(
         test.data.id,
         _,
         `StudentTestId(studentTest.data.id),
         ApolloGiveQuestionToTest(
           /* TODO this is running in wrong order */
           () =>
             giveQuestionToTestMutation(
               ~id=studentQuestion.data.id,
               ~originalId=
                 Schema.getQuestionUUIDFromId(
                   studentQuestion.data.originalId,
                 ),
               ~studentTestId=studentTest.data.id,
             ),
         ),
       );
};