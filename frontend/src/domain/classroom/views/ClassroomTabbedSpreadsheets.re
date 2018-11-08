let component = ReasonReact.statelessComponent("ClassroomTabbedSpreadsheets");

let fullsizeStyle = ReactDOMRe.Style.make(~height="100%", ~width="100%", ());

let make =
    (
      ~classroom: Classroom.Model.Record.t,
      ~normalized,
      ~updateNormalizr:
         Js.Promise.t(MyNormalizr.normalizedType) => Js.Promise.t('a),
      _children,
    ) => {
  ...component,
  render: _self => {
    let selectedTab =
      switch (classroom.local.testTab) {
      | "" =>
        classroom.data.testIds
        |> Belt.List.head
        |> Belt.Option.mapWithDefault(_, "", Schema.getUUIDFromId)
      | a => a
      };

    <div style=fullsizeStyle>
      {
        normalized
        |> MyNormalizr.Converter.Test.Remote.getRecord(
             _,
             `TestId(selectedTab),
           )
        |> (
          optionTest =>
            switch (optionTest) {
            | None => <div />
            | Some(test) =>
              <TestTabbedSpreadsheets
                headerSection={
                  <ClassroomSelectorPicker
                    classroom
                    normalized
                    updateNormalizr
                    testIds={classroom.data.testIds}
                    showStudentSelector=false
                  />
                }
                test
                normalized
                students={
                  classroom.data.studentIds
                  |> MyNormalizr.idListToFilteredItems(
                       _,
                       MyNormalizr.Converter.Student.Remote.getRecord(
                         normalized,
                       ),
                     )
                }
                updateTest=(
                  action =>
                    MyNormalizr.Converter.Test.Remote.updateWithDefault(
                      (),
                      normalized |> Js.Promise.resolve,
                      `TestId(test.data.id),
                      action,
                    )
                    |> updateNormalizr
                )
              />
            }
        )
      }
    </div>;
  },
};