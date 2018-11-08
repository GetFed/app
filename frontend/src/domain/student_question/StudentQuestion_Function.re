let getStudentAnswerKeys =
    (
      normalized,
      question: Question.Model.Record.t,
      studentQuestion: StudentQuestion.Model.Record.t,
    ) => {
  let questionBaseId =
    switch (question) {
    | LongAnswerQuestion(question) => question.data.questionBaseId
    | MultipleChoiceQuestion(question) => question.data.questionBaseId
    };
  let questionBase =
    normalized
    |> MyNormalizr.Converter.QuestionBase.Remote.getRecord(_, questionBaseId)
    |> Belt.Option.getWithDefault(
         _,
         QuestionBase.Model.Record.defaultWithId((), questionBaseId),
       );

  questionBase.data.answerKeyIds
  |> Belt.List.map(_, answerKeyId =>
       studentQuestion.data.answerKeyIds
       |> MyNormalizr.idListToFilteredItems(
            _,
            MyNormalizr.Converter.StudentAnswerKey.Remote.getRecord(
              normalized,
            ),
          )
       |> Belt.List.getBy(_, studentAnswerKey =>
            studentAnswerKey.data.originalId == answerKeyId
          )
       |> Belt.Option.getWithDefault(
            _,
            StudentAnswerKey.Model.Record.default(
              answerKeyId |> Schema.getUUIDFromId,
            ),
          )
     );
};

let createStudentQuestionAddKeyAnswer =
    (
      question: Question.Model.Record.t,
      studentQuestion: StudentQuestion.Model.Record.t,
      giveAnswerKeyToQuestionMutation,
      studentAnswerKey: StudentAnswerKey.Model.Record.t,
      norm,
    ) => {
  let typedId =
    switch (question) {
    | LongAnswerQuestion(question) =>
      Schema.LongAnswer(
        LongAnswerQuestion.Model.idToTypedId(question.data.id),
      )
    | MultipleChoiceQuestion(question) =>
      Schema.MultipleChoice(
        LongAnswerQuestion.Model.idToTypedId(question.data.id),
      )
    };

  let numAnswerKeysInList =
    studentQuestion.data.answerKeyIds
    |> Belt.List.keep(_, answerKeyId =>
         answerKeyId |> Schema.getUUIDFromId == studentAnswerKey.data.id
       )
    |> Belt.List.length;

  let hasAnswerKeyInList = numAnswerKeysInList != 0;

  hasAnswerKeyInList ?
    norm :
    norm
    |> MyNormalizr.Converter.StudentQuestion.Remote.updateWithDefault(
         typedId,
         _,
         `StudentQuestionId(studentQuestion.data.id),
         ApolloGiveAnswerKeyToQuestion(
           () =>
             giveAnswerKeyToQuestionMutation(
               ~id=studentAnswerKey.data.id,
               ~originalId=
                 studentAnswerKey.data.originalId |> Schema.getUUIDFromId,
               ~studentQuestionId=studentQuestion.data.id,
             ),
         ),
       );
};
let createUpdateStudentAnswer =
    (
      normalized,
      updateNormalizedWithReducer,
      updateNormalizr,
      question: Question.Model.Record.t,
      studentQuestion: StudentQuestion.Model.Record.t,
      studentAnswerKeys,
      studentQuestionAddKeyAnswer,
      updateStudentQuestionMutation,
      updateStudentAnswerKey,
    ) => {
  let questionId =
    switch (question) {
    | LongAnswerQuestion(question) =>
      Schema.LongAnswer(
        LongAnswerQuestion.Model.idToTypedId(question.data.id),
      )
    | MultipleChoiceQuestion(question) =>
      Schema.MultipleChoice(
        MultipleChoiceQuestion.Model.idToTypedId(question.data.id),
      )
    };

  let reduceNormalizedAllAnswerKeys = (memoNormalized, action) =>
    Belt.List.reduce(
      studentAnswerKeys,
      memoNormalized,
      (memoNormalized, studentAnswerKey: StudentAnswerKey.Model.Record.t) =>
      memoNormalized
      |> studentQuestionAddKeyAnswer(studentAnswerKey)
      |> MyNormalizr.Converter.StudentAnswerKey.Remote.updateWithDefault(
           studentAnswerKey.data.originalId |> Schema.getUUIDFromId,
           _,
           `StudentAnswerKeyId(studentAnswerKey.data.id),
           action,
         )
    );

  /* this is kind of confusing */
  let normalizedAllStudentKeys = (memoNormalized, correct) =>
    reduceNormalizedAllAnswerKeys(
      memoNormalized,
      StudentAnswerKey.Action.ApollSetCorrect(
        updateStudentAnswerKey,
        correct,
      ),
    ); /* thus feels weird */

  let normaliedStudentQuestion = (norm, action) =>
    MyNormalizr.Converter.StudentQuestion.Remote.updateWithDefault(
      questionId,
      norm,
      `StudentQuestionId(studentQuestion.data.id),
      action,
    );

  answer =>
    normalized
    |> Js.Promise.resolve
    |> updateNormalizedWithReducer
    |> normaliedStudentQuestion(
         _,
         StudentQuestion.Action.ApolloUpdateStudentQuestion(
           () =>
             updateStudentQuestionMutation(
               ~id=studentQuestion.data.id,
               ~answer,
             ),
         ),
       )
    |> (
      norm => {
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
        (
          questionBase.data.autoScore ?
            /* this is kind of confusing YUCK */
            normalizedAllStudentKeys(
              norm,
              answer == questionBase.data.solution,
            ) :
            norm
        )
        |> updateNormalizr;
      }
    );
};