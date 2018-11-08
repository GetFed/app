/* need to exist before everything */
type modelIdType = [
  | `TeacherId(UUID.t)
  | `ClassroomId(UUID.t)
  | `StudentId(UUID.t)
  | `StudentTestId(UUID.t)
  | `TestId(UUID.t)
  | `QuestionBaseId(UUID.t)
  | `LongAnswerQuestionId(UUID.t)
  | `MultipleChoiceQuestionId(UUID.t)
  | `StimulusId(UUID.t)
  | `QuestionAnswerKeyId(UUID.t)
  | `StudentQuestionId(UUID.t)
  | `StudentAnswerKeyId(UUID.t)
  | `ObjectiveId(UUID.t)
  | `MultipleChoiceId(UUID.t)
  | `UserId(UUID.t)
  | `GradeId(UUID.t)
];

/* pass as type id to domains */
type teacherId('a) = [> | `TeacherId(UUID.t)] as 'a;
type classroomId('a) = [> | `ClassroomId(UUID.t)] as 'a;
type studentId('a) = [> | `StudentId(UUID.t)] as 'a;
type studentTestId('a) = [> | `StudentTestId(UUID.t)] as 'a;
type testId('a) = [> | `TestId(UUID.t)] as 'a;
type stimulusId('a) = [> | `StimulusId(UUID.t)] as 'a;
type questionAnswerKeyId('a) = [> | `QuestionAnswerKeyId(UUID.t)] as 'a;
type longAnswerQuestionId('a) = [> | `LongAnswerQuestionId(UUID.t)] as 'a;
type questionBaseId('a) = [> | `QuestionBaseId(UUID.t)] as 'a;
type multipleChoiceQuestionId('a) =
  [> | `MultipleChoiceQuestionId(UUID.t)] as 'a;
type studentQuestionId('a) = [> | `StudentQuestionId(UUID.t)] as 'a;
type studentAnswerKeyId('a) = [> | `StudentAnswerKeyId(UUID.t)] as 'a;
type objectiveId('a) = [> | `ObjectiveId(UUID.t)] as 'a;
type multipleChoiceId('a) = [> | `MultipleChoiceId(UUID.t)] as 'a;
type userId('a) = [> | `UserId(UUID.t)] as 'a;
type gradeId('a) = [> | `GradeId(UUID.t)] as 'a;

type questionId('a) =
  | LongAnswer([> | `LongAnswerQuestionId(UUID.t)] as 'a)
  | MultipleChoice([> | `MultipleChoiceQuestionId(UUID.t)] as 'a);

/* Id only file above */

/* can belong to domain */
type schemaType = [
  | `TeacherSchema
  | `ClassroomSchema
  | `StudentSchema
  | `StudentTestSchema
  | `TestSchema
  | `QuestionBaseSchema
  | `LongAnswerQuestionSchema
  | `MultipleChoiceQuestionSchema
  | `StimulusSchema
  | `QuestionAnswerKeySchema
  | `StudentQuestionSchema
  | `StudentAnswerKeySchema
  | `ObjectiveSchema
  | `MultipleChoiceSchema
  | `UserSchema
  | `GradeSchema
];

/* Generate by Normalizr */
let modelIdToIdFunction = (recordIdType: modelIdType): (schemaType, UUID.t) =>
  switch (recordIdType) {
  | `TeacherId(uuid) => (`TeacherSchema, uuid)
  | `ClassroomId(uuid) => (`ClassroomSchema, uuid)
  | `StudentId(uuid) => (`StudentSchema, uuid)
  | `StudentTestId(uuid) => (`StudentTestSchema, uuid)
  | `TestId(uuid) => (`TestSchema, uuid)
  | `LongAnswerQuestionId(uuid) => (`LongAnswerQuestionSchema, uuid)
  | `QuestionBaseId(uuid) => (`QuestionBaseSchema, uuid)
  | `MultipleChoiceQuestionId(uuid) => (`MultipleChoiceQuestionSchema, uuid)
  | `StimulusId(uuid) => (`StimulusSchema, uuid)
  | `QuestionAnswerKeyId(uuid) => (`QuestionAnswerKeySchema, uuid)
  | `StudentQuestionId(uuid) => (`StudentQuestionSchema, uuid)
  | `StudentAnswerKeyId(uuid) => (`StudentAnswerKeySchema, uuid)
  | `ObjectiveId(uuid) => (`ObjectiveSchema, uuid)
  | `MultipleChoiceId(uuid) => (`MultipleChoiceSchema, uuid)
  | `UserId(uuid) => (`UserSchema, uuid)
  | `GradeId(uuid) => (`GradeSchema, uuid)
  };

/* can come from normalizr module */
let getUUIDFromId = (idType: modelIdType): UUID.t =>
  snd(modelIdToIdFunction(idType));

let getQuestionUUIDFromId = (qid: questionId(modelIdType)): UUID.t =>
  switch (qid) {
  | LongAnswer(longAnswerId) => getUUIDFromId(longAnswerId)
  | MultipleChoice(multipleChoiceId) => getUUIDFromId(multipleChoiceId)
  };