let component = ReasonReact.statelessComponent("App");

let make = /*~title, ~initialUrl, ~server : bool, */ _children => {
  ...component,
  render: (_self) =>
    <ReasonApollo.Provider client=Client.apiInstance>
      <FrontendRouter />
    </ReasonApollo.Provider>,
};

let default =
  ReasonReact.wrapReasonForJs(~component, _jsProps =>
    make([|
      /* ~server=(
           jsProps##server
           |> Js.undefinedToOption
           |> Belt.Option.getWithDefault(_, false)
         ), */
      /* ~initialUrl=Js.undefinedToOption(jsProps##initialUrl), */
    |])
  );