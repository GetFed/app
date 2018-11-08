let component = ReasonReact.statelessComponent("UserContainer");

module UserContainer = User_Model.Container;

let make = (~id, children) => {
  ...component,
  render: _ =>
    <UserContainer
      fragmentType=User_Model.fragmentType
      id
      fragmentName=User_Model.fragmentName>
      ...{(~data) => children(~user=data |> User_Model.Record.fromObject)}
    </UserContainer>,
};