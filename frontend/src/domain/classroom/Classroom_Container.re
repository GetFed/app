let component = ReasonReact.statelessComponent("ClassroomContainer");

module ClassroomContainer = Classroom_Model.Container;

let make = (~id, children) => {
  ...component,
  render: _ =>
    <ClassroomContainer
      fragmentType="Classroom" id fragmentName="classroomFields">
      ...{
           (~data) =>
             children(~classroom=data |> Classroom_Model.Record.fromObject)
         }
    </ClassroomContainer>,
};