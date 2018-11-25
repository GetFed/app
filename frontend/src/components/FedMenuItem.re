let component = ReasonReact.statelessComponent("FedMenuItem");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let fedMenuItemMainClass = [%bs.raw {| css(tw`
  mb-3
  text-sm
  cursor-pointer
  hover:opacity-75
`)|}];

let fedMenuInactiveLinkClass = [%bs.raw {| css(tw`
  text-green-darker
`)|}];

let fedMenuActiveLinkClass = [%bs.raw {| css(tw`
  text-orange-light
  pointer-events-none
`)|}];

let circleInfoClass = (active) => 
  cx(fedMenuItemMainClass, active ? fedMenuActiveLinkClass : fedMenuInactiveLinkClass);

let make = (~selected: bool, children) => {
  ...component,
  render: _self =>
  <div className=(circleInfoClass(selected))>
    {children |> ReasonReact.array}
  </div>
};