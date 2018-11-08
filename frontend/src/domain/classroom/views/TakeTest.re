let component = ReasonReact.statelessComponent("TakeTest");

let fullsizeStyle =
  ReactDOMRe.Style.make(
    ~height="100%",
    ~width="100%",
    ~display="flex",
    ~flexDirection="column",
    (),
  );

let selectionPickerStyle =
  ReactDOMRe.Style.make(~width="100%", ~marginBottom="1.5em", ());

let remainingStyle =
  ReactDOMRe.Style.make(~width="100%", ~flex="2", ~overflow="auto", ());

let make =
    (
      ~classroom: Classroom.Model.Record.t,
      ~normalized,
      ~updateNormalizr:
         Js.Promise.t(MyNormalizr.normalizedType) => Js.Promise.t('a),
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
    <Classroom.Mutation.GiveTestToClassroom>
      ...{
           (~mutation as giveTestToClassroomMutation) =>
             <div style=fullsizeStyle>
               <div style=selectionPickerStyle>
                 <ClassroomSelectorPicker
                   classroom
                   normalized
                   testIds
                   updateNormalizr
                   showStudentSelector=true
                 />
               </div>
               {
                 normalized
                 |> MyNormalizr.Converter.Student.Remote.getRecord(
                      _,
                      `StudentId(selectedStudent),
                    )
                 |> Belt.Option.mapWithDefault(_, <div />, student =>
                      testIds
                      |> Belt.List.getBy(_, testId =>
                           selectedTest == (testId |> Schema.getUUIDFromId)
                         )
                      |> Belt.Option.mapWithDefault(_, <div />, testId =>
                           student.data.testIds
                           |> MyNormalizr.idListToFilteredItems(
                                _,
                                MyNormalizr.Converter.StudentTest.Remote.getRecord(
                                  normalized,
                                ),
                              )
                           |> Belt.List.getBy(_, studentTest =>
                                studentTest.data.originalId == testId
                              )
                           |> Belt.Option.getWithDefault(
                                _,
                                StudentTest.Model.Record.default(
                                  testId |> Schema.getUUIDFromId,
                                ),
                              )
                           |> (
                             studentTest =>
                               <div style=remainingStyle>
                                 <Student.Mutation.GiveTestToStudent>
                                   ...{
                                        (~giveTestToStudent) =>
                                          <TestWriter
                                            normalized
                                            updateNormalizr
                                            updateNormalizedWithReducer={
                                              Student_Function.updateClassroomAndStudentNormalizr(
                                                normalized,
                                                giveTestToClassroomMutation,
                                                giveTestToStudent,
                                                classroom: Classroom.Model.Record.t,
                                                studentTest: StudentTest.Model.Record.t,
                                                student: Student.Model.Record.t,
                                              )
                                            }
                                            studentTest
                                          />
                                      }
                                 </Student.Mutation.GiveTestToStudent>
                               </div>
                           )
                         )
                    )
               }
             </div>
         }
    </Classroom.Mutation.GiveTestToClassroom>;
  },
};