let component = ReasonReact.statelessComponent("TestContainer");

module TestContainer = Test_Model.Container;

let make = (~id, children) => {
  ...component,
  render: _ =>
    <TestContainer fragmentType="Test" id fragmentName="testFields">
      ...{(~data) => children(~test=data |> Test_Model.Record.fromObject)}
    </TestContainer>,
};