let component = ReasonReact.statelessComponent("RosterLayout");

let textStyle = ReactDOMRe.Style.make(~margin="1em", ());

let fullsizeStyle = ReactDOMRe.Style.make(~height="100%", ~width="100%", ());

let classNameTextStyle =
  ReactDOMRe.Style.make(~width="100%", ~borderBottom="solid 1px gray", ());

let make =
    (
      ~classroom: Classroom.Model.Record.t,
      ~testIds,
      ~normalized,
      ~updateNormalizr:
         Js.Promise.t(MyNormalizr.normalizedType) => Js.Promise.t('a),
      _children,
    ) => {
  ...component,
  render: _self => {
    let updateClassroom = action =>
      MyNormalizr.Converter.Classroom.Remote.updateWithDefault(
        (),
        normalized |> Js.Promise.resolve,
        `ClassroomId(classroom.data.id),
        action,
      )
      |> updateNormalizr;

    let studentHasEmptyField =
      classroom.data.studentIds
      |> MyNormalizr.idListToFilteredItems(
           _,
           MyNormalizr.Converter.Student.Remote.getRecord(normalized),
         )
      |> Belt.List.keep(_, student =>
           student.data.firstName === "" && student.data.lastName === ""
         )
      |> Belt.List.length;

    let selectedTest =
      switch (classroom.local.testTab) {
      | "" =>
        testIds
        |> Belt.List.head
        |> Belt.Option.mapWithDefault(_, "", Schema.getUUIDFromId)
      | a => a
      };

    <div style=fullsizeStyle>
      <Classroom.Mutation.AddStudent
        id={classroom.local.newStudentId |> Schema.getUUIDFromId}
        classroomId={classroom.data.id}>
        ...{
             (~addStudent) =>
               <div>
                 <StudentRowHeader
                   normalized
                   classroom
                   testIds
                   updateNormalizr
                   addingNewStudent={studentHasEmptyField > 0}
                   addStudent={
                     _ =>
                       updateClassroom(
                         Classroom.Action.ApolloAddStudent(addStudent),
                       )
                       |> ignore
                   }
                 />
               </div>
           }
      </Classroom.Mutation.AddStudent>
      {
        classroom.data.studentIds
        |> Belt.List.map(
             _,
             studentId => {
               let student =
                 normalized
                 |> MyNormalizr.Converter.Student.Remote.getRecord(
                      _,
                      studentId,
                    )
                 |> Belt.Option.getWithDefault(
                      _,
                      Student.Model.Record.default(),
                    );
               let updateStudent = action =>
                 MyNormalizr.Converter.Student.Remote.updateWithDefault(
                   (),
                   normalized |> Js.Promise.resolve,
                   `StudentId(student.data.id),
                   action,
                 )
                 |> updateNormalizr;

               <StudentRow
                 key={student.data.id}
                 classroom
                 student
                 updateStudent
                 selectedTest
               />;
             },
           )
        |> Utils.ReasonReact.listToReactArray
      }
    </div>;
  },
};