let component = ReasonReact.statelessComponent("FedMenuLink");

let css = Css.css;
let tw = Css.tw;

let fedMenuLinkClass = [%bs.raw {| css(tw`
  text-green-darker
  mb-4
`)|}];

let fedMenuActiveLinkClass = [%bs.raw {| css(tw`
  text-orange-light
  mb-4
`)|}];

let make = (~selected: bool, ~text: string, _children) => {
  ...component,
  render: _self =>
  <div className=(selected ? fedMenuActiveLinkClass : fedMenuLinkClass)>
    {ReasonReact.string(text)}
  </div>
};