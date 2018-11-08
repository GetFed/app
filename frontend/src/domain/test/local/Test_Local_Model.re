type _record = {
  newQuestionId: Schema.questionId(Schema.modelIdType),
  newObjectiveId: Schema.objectiveId(Schema.modelIdType),
  editingName: bool,
  editingDescription: bool,
  resultTab: ResultTab.t,
  questionTab: QuestionTab.t,
  overviewGraphDisplay: OverviewGraphDisplay.t,
  selectedQuestion: option(UUID.t),
};

let _defaultRecord = id => {
  module UUIDSeedType = {
    let namespace = id;
  };

  module Rand = UUID.V5Random(UUIDSeedType);
  {
    newQuestionId: LongAnswer(`LongAnswerQuestionId(Rand.generateSeqUUID())),
    newObjectiveId: `ObjectiveId(Rand.generateSeqUUID()),
    editingName: false,
    editingDescription: false,
    resultTab: ResultTab.Overview,
    questionTab: QuestionTab.Overview,
    overviewGraphDisplay: OverviewGraphDisplay.Mastery,
    selectedQuestion: None,
  };
};

module Record = {
  type t = _record;
  let default = _defaultRecord;
};