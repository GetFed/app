let component = ReasonReact.statelessComponent("TestTabbedSpreadsheets");

let fullsizeStyle = ReactDOMRe.Style.make(~height="100%", ~width="100%", ());

let tabbedStyles =
  ReactDOMRe.Style.make(
    ~width="100%",
    ~display="flex",
    ~justifyContent="center",
    (),
  );

let emptyDivStyle = ReactDOMRe.Style.make(~width="9.3em", ());

let tabTypeToComponent =
    (resultTabType, normalized, test, students, updateTest) =>
  switch (resultTabType) {
  | ResultTab.Overview =>
    <TestScoreGraph normalized test students updateTest />
  | ResultTab.Score =>
    <TestAnswerKeySpreadsheet normalized test students updateTest />
  | ResultTab.Objective =>
    <TestObjectiveSpreadsheet normalized test students />
  | ResultTab.Question =>
    <TestQuestionDetailsSpreadsheet normalized test students />
  };
let flexStyle =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~justifyContent="space-between",
    ~marginBottom="1em",
    (),
  );

let make =
    (
      ~test: Test.Model.Record.t,
      ~students,
      ~headerSection: ReasonReact.reactElement,
      ~updateTest,
      ~normalized,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div style=fullsizeStyle>
      <div style=flexStyle>
        headerSection
        <TabNav>
          <div style=tabbedStyles>
            {
              ResultTab.all
              |> Belt.List.map(
                   _,
                   resultTabType => {
                     let resultTabString =
                       resultTabType |> ResultTab.resultTypeTabToString;
                     <TabNavItem key=resultTabString>
                       <TabNavLink
                         className={
                           test.local.resultTab == resultTabType ?
                             "active" : ""
                         }
                         onClick={
                           () =>
                             updateTest(
                               Test.Action.SelectResultTab(resultTabType),
                             )
                             |> ignore
                         }>
                         {ReasonReact.string(resultTabString)}
                       </TabNavLink>
                     </TabNavItem>;
                   },
                 )
              |> Utils.ReasonReact.listToReactArray
            }
          </div>
        </TabNav>
        <div style=emptyDivStyle />
      </div>
      <Tabs activeTab={ResultTab.resultTypeTabToString(test.local.resultTab)}>
        {
          ResultTab.all
          |> Belt.List.keep(_, resultTabType =>
               resultTabType == test.local.resultTab
             )  /* monkey patch... should do fuller solution*/
          |> Belt.List.map(
               _,
               resultTabType => {
                 let resultTabString =
                   resultTabType |> ResultTab.resultTypeTabToString;
                 <Tab key=resultTabString tabId=resultTabString>
                   {
                     tabTypeToComponent(
                       resultTabType,
                       normalized,
                       test,
                       students,
                       updateTest,
                     )
                   }
                 </Tab>;
               },
             )
          |> Utils.ReasonReact.listToReactArray
        }
      </Tabs>
    </div>,
};