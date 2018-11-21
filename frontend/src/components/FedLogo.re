let component = ReasonReact.statelessComponent("FedLogo");

let css = Css.css;
let tw = Css.tw;

let logoClass = [%bs.raw {| css(tw`
  bg-contain
  bg-no-repeat
  bg-center
  h-32
`)|}];

let make = (_children) => {
  ...component,
  render: _self =>
    <div className=(logoClass ++ " bg-logo")>
    </div>,
};