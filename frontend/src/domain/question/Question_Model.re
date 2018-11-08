/* not can't put the following into a union and pass around */

type _record =
  | LongAnswerQuestion(LongAnswerQuestion.Model.Record.t)
  | MultipleChoiceQuestion(MultipleChoiceQuestion.Model.Record.t);

type idType = Schema.questionId(Schema.modelIdType);

type questionTypeObj = [
  | `LongAnswerQuestion(LongAnswerQuestion.Model.Fragment.Fields.t)
  | `MultipleChoiceQuestion(MultipleChoiceQuestion.Model.Fragment.Fields.t)
];

module Fragment = {
  module QuestionFields = {
    type t = questionTypeObj;
  };
};
/* let idToTypedId = (id: UUID.t): idType => id; */
let objectToId = (obj: questionTypeObj): idType =>
  switch (obj) {
  | `LongAnswerQuestion(q) =>
    LongAnswer(LongAnswerQuestion.Model.objectToId(q))
  | `MultipleChoiceQuestion(q) =>
    MultipleChoice(MultipleChoiceQuestion.Model.objectToId(q))
  };

let objectToFragment = (obj: questionTypeObj): questionTypeObj =>
  switch (obj) {
  | `LongAnswerQuestion(q) => `LongAnswerQuestion(q)
  | `MultipleChoiceQuestion(q) => `MultipleChoiceQuestion(q)
  };

module Record = {
  type t = _record;
  let defaultWithId = (id: idType): _record =>
    switch (id) {
    | LongAnswer(id) =>
      LongAnswerQuestion(
        LongAnswerQuestion.Model.Record.defaultWithId((), id),
      )
    | MultipleChoice(id) =>
      MultipleChoiceQuestion(
        MultipleChoiceQuestion.Model.Record.defaultWithId((), id),
      )
    };
};

let getById = (id: idType): option(questionTypeObj) =>
  switch (id) {
  | LongAnswer(laqId) =>
    LongAnswerQuestion.Model.getById(laqId)
    |> Belt.Option.map(_, obj => `LongAnswerQuestion(obj))
  | MultipleChoice(mcId) =>
    MultipleChoiceQuestion.Model.getById(mcId)
    |> Belt.Option.map(_, obj => `MultipleChoiceQuestion(obj))
  };

let questionToString = (question: Record.t): string =>
  switch (question) {
  | MultipleChoiceQuestion(_) => "Multiple Choice"
  | LongAnswerQuestion(_) => "Long Response"
  };