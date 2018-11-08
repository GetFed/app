type recordType = [
  | `Teacher(Teacher.Model.Record.t)
  | `Classroom(Classroom.Model.Record.t)
  | `Student(Student.Model.Record.t)
  | `StudentTest(StudentTest.Model.Record.t)
  | `Test(Test.Model.Record.t)
  | `LongAnswerQuestion(LongAnswerQuestion.Model.Record.t)
  | `QuestionBase(QuestionBase.Model.Record.t)
  | `MultipleChoiceQuestion(MultipleChoiceQuestion.Model.Record.t)
  | `Stimulus(Stimulus.Model.Record.t)
  | `QuestionAnswerKey(QuestionAnswerKey.Model.Record.t)
  | `StudentQuestion(StudentQuestion.Model.Record.t)
  | `StudentAnswerKey(StudentAnswerKey.Model.Record.t)
  | `Objective(Objective.Model.Record.t)
  | `MultipleChoice(MultipleChoice.Model.Record.t)
];

module type DomainWrapper = {
  type model;
  let wrap: model => recordType;
  let unwrap: recordType => option(model);
  let apolloEnabled: bool;
};

module Wrapper = {
  module Teacher = {
    type model = Teacher.Model.Record.t;
    let wrap = model => `Teacher(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Teacher(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module Classroom = {
    type model = Classroom.Model.Record.t;
    let wrap = model => `Classroom(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Classroom(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
  module Student = {
    type model = Student.Model.Record.t;
    let wrap = model => `Student(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Student(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
  module StudentTest = {
    type model = StudentTest.Model.Record.t;
    let wrap = model => `StudentTest(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `StudentTest(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
  module Test = {
    type model = Test.Model.Record.t;
    let wrap = model => `Test(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Test(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
  module LongAnswerQuestion = {
    type model = LongAnswerQuestion.Model.Record.t;
    let wrap = model => `LongAnswerQuestion(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `LongAnswerQuestion(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
  module QuestionBase = {
    type model = QuestionBase.Model.Record.t;
    let wrap = model => `QuestionBase(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `QuestionBase(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module MultipleChoiceQuestion = {
    type model = MultipleChoiceQuestion.Model.Record.t;
    let wrap = model => `MultipleChoiceQuestion(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `MultipleChoiceQuestion(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
  module Stimulus = {
    type model = Stimulus.Model.Record.t;
    let wrap = model => `Stimulus(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Stimulus(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
  module QuestionAnswerKey = {
    type model = QuestionAnswerKey.Model.Record.t;
    let wrap = model => `QuestionAnswerKey(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `QuestionAnswerKey(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
  module StudentQuestion = {
    type model = StudentQuestion.Model.Record.t;
    let wrap = model => `StudentQuestion(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `StudentQuestion(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
  module StudentAnswerKey = {
    type model = StudentAnswerKey.Model.Record.t;
    let wrap = model => `StudentAnswerKey(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `StudentAnswerKey(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
  module Objective = {
    type model = Objective.Model.Record.t;
    let wrap = model => `Objective(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Objective(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
  module MultipleChoice = {
    type model = MultipleChoice.Model.Record.t;
    let wrap = model => `MultipleChoice(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `MultipleChoice(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
};

/* Can be put into normizr */
let modelTypeToRecordType =
    (recordType: recordType): (Schema.schemaType, UUID.t) =>
  switch (recordType) {
  | `Teacher(teacher) => (`TeacherSchema, teacher.data.id)
  | `Classroom(classroom) => (`ClassroomSchema, classroom.data.id)
  | `Student(student) => (`StudentSchema, student.data.id)
  | `StudentTest(studentTest) => (`StudentTestSchema, studentTest.data.id)
  | `Test(test) => (`TestSchema, test.data.id)
  | `QuestionBase(question) => (`QuestionBaseSchema, question.data.id)
  | `LongAnswerQuestion(question) => (
      `LongAnswerQuestionSchema,
      question.data.id,
    )
  | `MultipleChoiceQuestion(question) => (
      `MultipleChoiceQuestionSchema,
      question.data.id,
    )
  | `Stimulus(stimulus) => (`StimulusSchema, stimulus.data.id)
  | `QuestionAnswerKey(questionAnswerKey) => (
      `QuestionAnswerKeySchema,
      questionAnswerKey.data.id,
    )
  | `StudentQuestion(studentQuestion) => (
      `StudentQuestionSchema,
      studentQuestion.data.id,
    )
  | `StudentAnswerKey(studentAnswerKey) => (
      `StudentAnswerKeySchema,
      studentAnswerKey.data.id,
    )
  | `Objective(objective) => (`ObjectiveSchema, objective.data.id)
  | `MultipleChoice(multipleChoice) => (
      `MultipleChoiceSchema,
      multipleChoice.data.id,
    )
  };

type normalizedType =
  NormalizrNew.normalizedSchema(Schema.schemaType, UUID.t, recordType);

let normalizerCommitItemToSchema:
  (normalizedType, recordType) => normalizedType =
  NormalizrNew.Normalizr.commitItemToSchema(modelTypeToRecordType);

let normalizerGetItemFromSchema:
  (normalizedType, Schema.modelIdType) => option(recordType) =
  NormalizrNew.Normalizr.getItemFromSchema(Schema.modelIdToIdFunction);

let idListToFilteredItems =
    (idList: list(Schema.modelIdType), modelTypefunction) =>
  idList
  |> Belt.List.map(_, modelTypefunction)
  |> Utils.List.removeOptionsFromList;

let tryAgainifNullOption = (optionA, optionB) =>
  switch (optionA) {
  | Some(_) => optionA
  | None => optionB
  };

module DomainTypeConverter =
       (
         DomainType: Domain.M,
         Wrapper: DomainWrapper with type model = DomainType.Model.Record.t,
       ) => {
  let update =
      (
        default: Schema.modelIdType => DomainType.Model.Record.t,
        getterFn:
          (normalizedType, Schema.modelIdType) =>
          option(DomainType.Model.Record.t),
        reduce:
          (DomainType.Action.action, Js.Promise.t(DomainType.Action.model)) =>
          Js.Promise.t(DomainType.Action.model),
        normalized: Js.Promise.t(normalizedType),
        id: Schema.modelIdType,
        action: DomainType.Action.action,
      )
      : Js.Promise.t(normalizedType) => {
    let modelPromise =
      normalized
      |> Js.Promise.then_(norm =>
           norm
           |> getterFn(_, id)
           |> Belt.Option.getWithDefault(_, default(id))
           |> Js.Promise.resolve
         )
      |> reduce(action, _);

    (normalized, modelPromise)
    |> Js.Promise.all2
    |> Js.Promise.then_(((norm, model)) =>
         Js.Promise.resolve(
           normalizerCommitItemToSchema(norm, Wrapper.wrap(model)),
         )
       );
  };
  let fromLocal =
      (
        normalized: normalizedType,
        id: Schema.modelIdType /* maybe make domain model idtype*/,
      )
      : option(DomainType.Model.Record.t) =>
    normalized
    |> normalizerGetItemFromSchema(_, id)
    |> Belt.Option.flatMap(_, Wrapper.unwrap);

  let fromSchema =
      (
        normalized: normalizedType,
        id: Schema.modelIdType /* maybe make domain model idtype*/,
      )
      : option(DomainType.Model.Record.t) => {
    let optionNormalized = fromLocal(normalized, id);

    Wrapper.apolloEnabled ?
      id
      |> DomainType.Model.getById
      |> Belt.Option.map(_, (fragment: DomainType.Model.Fragment.Fields.t) =>
           (
             switch (optionNormalized) {
             | Some(data) => {
                 local: data.local,
                 data: DomainType.Model.Record.Data.fromObject(fragment),
               }
             | None => DomainType.Model.Record.fromObject(fragment) /* does this also generate the local? */
             }: DomainType.Model.Record.t
           )
         )
      |> tryAgainifNullOption(_, optionNormalized) :
      optionNormalized;
  };

  module Local = {
    let getRecord = fromLocal;
    let getRecordWithDefault =
        (
          normalized: normalizedType,
          id: Schema.modelIdType,
          param: DomainType.Model.Record.defaultParam,
        )
        : DomainType.Model.Record.t =>
      normalized
      |> fromLocal(_, id)
      |> Belt.Option.getWithDefault(
           _,
           DomainType.Model.Record.defaultWithId(param, id),
         );

    let updateWithDefault = (param: DomainType.Model.Record.defaultParam) =>
      update(
        DomainType.Model.Record.defaultWithId(param, _),
        fromLocal,
        DomainType.Action.reduce,
      );
  };

  module Remote = {
    let getRecord = fromSchema;
    let getRecordWithDefault =
        (
          normalized: normalizedType,
          id: Schema.modelIdType,
          param: DomainType.Model.Record.defaultParam,
        )
        : DomainType.Model.Record.t =>
      normalized
      |> fromSchema(_, id)
      |> Belt.Option.getWithDefault(
           _,
           DomainType.Model.Record.defaultWithId(param, id),
         );

    let updateWithDefault = (param: DomainType.Model.Record.defaultParam) =>
      update(
        DomainType.Model.Record.defaultWithId(param, _),
        fromSchema, /* How does this handle the llocal??????? */
        DomainType.Action.reduce,
      );
  };
};

module Converter = {
  module Teacher = DomainTypeConverter(Teacher, Wrapper.Teacher);
  module Classroom = DomainTypeConverter(Classroom, Wrapper.Classroom);
  module Student = DomainTypeConverter(Student, Wrapper.Student);
  module StudentTest = DomainTypeConverter(StudentTest, Wrapper.StudentTest);
  module Test = DomainTypeConverter(Test, Wrapper.Test);
  module QuestionBase =
    DomainTypeConverter(QuestionBase, Wrapper.QuestionBase);
  module MultipleChoiceQuestion =
    DomainTypeConverter(
      MultipleChoiceQuestion,
      Wrapper.MultipleChoiceQuestion,
    );
  module LongAnswerQuestion =
    DomainTypeConverter(LongAnswerQuestion, Wrapper.LongAnswerQuestion);
  module Stimulus = DomainTypeConverter(Stimulus, Wrapper.Stimulus);
  module QuestionAnswerKey =
    DomainTypeConverter(QuestionAnswerKey, Wrapper.QuestionAnswerKey);
  module StudentQuestion =
    DomainTypeConverter(StudentQuestion, Wrapper.StudentQuestion);
  module StudentAnswerKey =
    DomainTypeConverter(StudentAnswerKey, Wrapper.StudentAnswerKey);
  module Objective = DomainTypeConverter(Objective, Wrapper.Objective);
  module MultipleChoice =
    DomainTypeConverter(MultipleChoice, Wrapper.MultipleChoice);
};

let localGetQuestionFromSchema =
    (normalized, id): option(Question.Model.Record.t) =>
  switch (id) {
  | Schema.LongAnswer(id) =>
    Converter.LongAnswerQuestion.Local.getRecord(normalized, id)
    |> Belt.Option.map(_, q => Question.Model.LongAnswerQuestion(q))
  | Schema.MultipleChoice(id) =>
    Converter.MultipleChoiceQuestion.Local.getRecord(normalized, id)
    |> Belt.Option.map(_, q => Question.Model.MultipleChoiceQuestion(q))
  };

let getQuestionFromSchema = (normalized, id): option(Question.Model.Record.t) =>
  switch (id) {
  | Schema.LongAnswer(id) =>
    Converter.LongAnswerQuestion.Remote.getRecord(normalized, id)
    |> Belt.Option.map(_, q => Question.Model.LongAnswerQuestion(q))
  | Schema.MultipleChoice(id) =>
    Converter.MultipleChoiceQuestion.Remote.getRecord(normalized, id)
    |> Belt.Option.map(_, q => Question.Model.MultipleChoiceQuestion(q))
  };