let component = ReasonReact.statelessComponent("App");

let make = (~initialUrl : option(string), /* ~title, ~server : bool, */ _children) => {
  ...component,
  render: (_self) =>
    <ReasonApollo.Provider client=Client.apiInstance>
      <FrontendRouter initialUrl />
    </ReasonApollo.Provider>,
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~initialUrl=(Js.undefinedToOption(jsProps##initialUrl)),
      /* ~server=(
           jsProps##server
           |> Js.undefinedToOption
           |> Belt.Option.getWithDefault(_, false)
         ), */
      [||])
  );