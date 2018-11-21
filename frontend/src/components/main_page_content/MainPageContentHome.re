let component = ReasonReact.statelessComponent("MainPageContentHome");

let css = Css.css;
let tw = Css.tw;

let backgroundImageClass = [%bs.raw {| css(tw`
  w-full
  h-screen
  bg-cover
  bg-center
`)|}];

let aboutUsSubscriptionClass = [%bs.raw {| css(tw`
  h-4
`)|}];

let make = (_children) => {
  ...component,
  render: _self =>
    <div>
      <div className=(backgroundImageClass ++ " bg-image") />
      <div className=aboutUsSubscriptionClass/>
    </div>
};