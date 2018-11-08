let component = ReasonReact.statelessComponent("TeacherContainer");

module TeacherContainer = Teacher_Model.Container;

let make = (~id, children) => {
  ...component,
  render: _ =>
    <TeacherContainer fragmentType="Teacher" id fragmentName="teacherFields">
      ...{
           (~data) =>
             children(~teacher=data |> Teacher_Model.Record.fromObject)
         }
    </TeacherContainer>,
};