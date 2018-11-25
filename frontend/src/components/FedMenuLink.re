let component = ReasonReact.statelessComponent("FedMenuLink");

let make = (~href: string, ~text: string, _children) => {
  ...component,
  render: _self =>
  <A href> {ReasonReact.string(text)} </A>
};