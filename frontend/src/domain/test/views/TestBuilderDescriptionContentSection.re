let component =
  ReasonReact.statelessComponent("TestBuilderDescriptionContentSection");

let testDescriptionTextStyle =
  ReactDOMRe.Style.make(
    ~backgroundColor="inherit",
    ~height="100%",
    ~width="100%",
    ~wordWrap="break-word",
    ~wordBreak="break-all",
    (),
  );

let make = (~test: Test.Model.Record.t, ~updateTest, _children) => {
  ...component,
  render: _self =>
    <Test.Mutation.UpdateTest>
      ...{
           (~mutation) =>
             <Editable
               key={test.data.id ++ "_description"}
               editing={test.local.editingDescription}
               editingToggle={
                 () => updateTest(Test.Action.ToggleEditDescription)
               }
               value={test.data.description}
               placeholder="Write description here"
               onTextChange={
                 text =>
                   updateTest(
                     Test.Action.ApolloUpdateTest(
                       () =>
                         mutation(
                           ~id=test.data.id,
                           ~name=test.data.name,
                           ~description=text,
                         ),
                     ),
                   )
               }
               style=testDescriptionTextStyle
               useTextArea=true
             />
         }
    </Test.Mutation.UpdateTest>,
};