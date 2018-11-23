/* need to exist before everything */
type modelIdType = [
  | `TeacherId(UUID.t)
  | `UserId(UUID.t)
  | `CustomerId(UUID.t)
  | `MenuId(UUID.t)
];

/* pass as type id to domains */
type teacherId('a) = [> | `TeacherId(UUID.t)] as 'a;
type customerId('a) = [> | `CustomerId(UUID.t)] as 'a;
type userId('a) = [> | `UserId(UUID.t)] as 'a;
type menuId('a) = [> | `MenuId(UUID.t)] as 'a;

/* just something to look at */
/* type questionId('a) =
  | LongAnswer([> | `LongAnswerQuestionId(UUID.t)] as 'a)
  | MultipleChoice([> | `MultipleChoiceQuestionId(UUID.t)] as 'a); */

/* Id only file above */

/* can belong to domain */
type schemaType = [
  | `TeacherSchema
  | `CustomerSchema
  | `UserSchema
  | `MenuSchema
];

/* Generate by Normalizr */
let modelIdToIdFunction = (recordIdType: modelIdType): (schemaType, UUID.t) =>
  switch (recordIdType) {
  | `TeacherId(uuid) => (`TeacherSchema, uuid)
  | `CustomerId(uuid) => (`CustomerSchema, uuid)
  | `UserId(uuid) => (`UserSchema, uuid)
  | `MenuId(uuid) => (`MenuSchema, uuid)
  };

/* can come from normalizr module */
let getUUIDFromId = (idType: modelIdType): UUID.t =>
  snd(modelIdToIdFunction(idType));

/* union example */
/* let getQuestionUUIDFromId = (qid: questionId(modelIdType)): UUID.t =>
  switch (qid) {
  | LongAnswer(longAnswerId) => getUUIDFromId(longAnswerId)
  | MultipleChoice(multipleChoiceId) => getUUIDFromId(multipleChoiceId)
  }; */