let component = ReasonReact.statelessComponent("Page_StudentTestLayout");

let make = (~testId: string, _children) => {
  ...component,
  render: _self =>
    <Page_Test_Container testId errorComponent={<LoginLayout />}>
      ...{
           (~testId) =>
             switch (testId) {
             | Some(testId) =>
               <Test.Container id=testId>
                 ...(
                      (~test) => {
                        Js.log("test");
                        Js.log(test);
                        <NormalizrInit records=[`Test(test)]>
                          ...{
                               (~normalized, ~updateNormalizr) =>
                                 <TestPreview
                                   testId={`TestId(testId)}
                                   normalized
                                 />
                             }
                        </NormalizrInit>;
                      }
                    )
               </Test.Container>
             | _ => <div />
             }
         }
    </Page_Test_Container>,
};