let component = ReasonReact.statelessComponent("CompnentIfExists");
let make = (~idFunction, ~normalized, ~id, ~render, _children) => {
  ...component,
  render:
    (_self) => Belt.Option.mapWithDefault(idFunction(normalized, id), <div />, render)
};
