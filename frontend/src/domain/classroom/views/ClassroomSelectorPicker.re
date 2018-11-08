let component = ReasonReact.statelessComponent("ClassroomSelectorPicker");

let fullWidthStyle =
  ReactDOMRe.Style.make(
    ~width="content-fit",
    ~display="flex",
    ~justifyContent="flex-start",
    (),
  );

let selectorStyle =
  ReactDOMRe.Style.make(~marginRight="1em", ~display="flex", ());

let textStyle = ReactDOMRe.Style.make(~marginRight="1em", ());

let make =
    (
      ~classroom: Classroom.Model.Record.t,
      ~normalized,
      ~updateNormalizr:
         Js.Promise.t(MyNormalizr.normalizedType) => Js.Promise.t('a),
      ~showStudentSelector,
      ~testIds,
      _children,
    ) => {
  ...component,
  render: _self => {
    let selectedTest =
      switch (classroom.local.testTab) {
      | "" =>
        testIds
        |> Belt.List.head
        |> Belt.Option.mapWithDefault(_, "", Schema.getUUIDFromId)
      | a => a
      };
    let selectedStudent =
      switch (classroom.local.selectedStudent) {
      | None =>
        classroom.data.studentIds
        |> Belt.List.head
        |> Belt.Option.mapWithDefault(_, "", Schema.getUUIDFromId)
      | Some(a) =>
        MyNormalizr.Converter.Student.Remote.getRecord(normalized, a)
        |> Belt.Option.mapWithDefault(_, "", student => student.data.id)
      };

    let updateClassroom = action =>
      MyNormalizr.Converter.Classroom.Remote.updateWithDefault(
        (),
        normalized |> Js.Promise.resolve,
        `ClassroomId(classroom.data.id),
        action,
      )
      |> updateNormalizr;

    <div style=fullWidthStyle>
      <div style=selectorStyle>
        <div style=textStyle> {ReasonReact.string("Test:")} </div>
        <div>
          <Select
            selectedId=selectedTest
            idToString={a => a}
            selections={
              testIds
              |> MyNormalizr.idListToFilteredItems(
                   _,
                   MyNormalizr.Converter.Test.Remote.getRecord(normalized),
                 )
              |> Belt.List.map(_, test =>
                   (
                     {id: test.data.id, text: test.data.name}:
                       Select.selectionType(UUID.t)
                   )
                 )
            }
            onSelect={
              a =>
                updateClassroom(
                  Classroom.Action.ChangeTestTab(
                    Belt.Option.getWithDefault(a, ""),
                  ),
                )
            }
          />
        </div>
      </div>
      {
        showStudentSelector ?
          <div style=selectorStyle>
            <div style=textStyle> {ReasonReact.string("Student:")} </div>
            <div>
              <Select
                selectedId=selectedStudent
                idToString={a => a}
                selections={
                  classroom.data.studentIds
                  |> MyNormalizr.idListToFilteredItems(
                       _,
                       MyNormalizr.Converter.Student.Remote.getRecord(
                         normalized,
                       ),
                     )
                  |> Belt.List.map(_, student =>
                       (
                         {id: student.data.id, text: student.data.firstName}:
                           Select.selectionType(UUID.t)
                       )
                     )
                }
                onSelect={
                  a =>
                    updateClassroom(
                      Classroom.Action.SelectStudent(
                        Some(`StudentId(Belt.Option.getWithDefault(a, ""))),
                      ),
                    )
                }
              />
            </div>
          </div> :
          <div />
      }
    </div>;
  },
};