type action =
  | ResetNewQuestion
  | ResetNewObjective
  | ToggleEditName
  | ToggleEditDescription
  | SelectResultTab(ResultTab.t)
  | ChangeSelectedQuestion(option(UUID.t))
  | ChangeGraphDisplay(OverviewGraphDisplay.t)
  | ChangeQuestionTabType(QuestionTab.t);

type model = Test_Local_Model.Record.t;

let reduce = (action, local: model): model => {
  let {editingName, editingDescription}: model = local;
  switch (action) {
  | ResetNewQuestion => {
      ...local,
      newQuestionId: LongAnswer(`LongAnswerQuestionId(UUID.generateUUID())),
    }
  | ResetNewObjective => {
      ...local,
      newObjectiveId: `ObjectiveId(UUID.generateUUID()),
    }
  | ToggleEditName => {...local, editingName: !editingName}
  | ToggleEditDescription => {
      ...local,
      editingDescription: !editingDescription,
    }
  | SelectResultTab(resultTab) => {...local, resultTab}
  | ChangeSelectedQuestion(selectedQuestion) => {...local, selectedQuestion}
  | ChangeGraphDisplay(overviewGraphDisplay) => {
      ...local,
      overviewGraphDisplay,
    }
  | ChangeQuestionTabType(questionTab) => {...local, questionTab}
  };
};