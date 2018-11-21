let component = ReasonReact.statelessComponent("FedMenuLink");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let fedMenuLinkMainClass = [%bs.raw {| css(tw`
  mb-4
  text-sm
  font-medium
`)|}];

let fedMenuInactiveLinkClass = [%bs.raw {| css(tw`
  text-green-darker
`)|}];

let fedMenuActiveLinkClass = [%bs.raw {| css(tw`
  text-orange-light
`)|}];

let circleInfoClass = (active) => 
  cx(fedMenuLinkMainClass, active ? fedMenuActiveLinkClass : fedMenuInactiveLinkClass);

let make = (~selected: bool, ~text: string, _children) => {
  ...component,
  render: _self =>
  <div className=(circleInfoClass(selected))>
    {ReasonReact.string(text)}
  </div>
};