let component = ReasonReact.statelessComponent("PageHome");

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

let make = (~pathIds, _children) => {
  ...component,
  render: _self =>
    <div>
      <FedSideMenu />
      <div className=(backgroundImageClass ++ " bg-image")>
      </div>
      <div className=aboutUsSubscriptionClass/>
    </div>
};