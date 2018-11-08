let component = ReasonReact.statelessComponent("StudentContainer");

module StudentContainer = Student_Model.Container;

let make = (~id, children) => {
  ...component,
  render: _ =>
    <StudentContainer fragmentType="Student" id fragmentName="studentFields">
      ...{
           (~data) =>
             children(~student=data |> Student_Model.Record.fromObject)
         }
    </StudentContainer>,
};