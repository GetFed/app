let component = ReasonReact.statelessComponent("MainPageContentHomeContainer");

let css = Css.css;
let tw = Css.tw;

let mainPageContentHomeClass = [%bs.raw {| css(tw`
  w-screen
  absolute
  pin-t
  pin-l
`)|}];

let backgroundImageClass = [%bs.raw {| css(tw`
  w-full
  h-screen
  bg-cover
  bg-center
  mb-8
`)|}];

let aboutUsSubscriptionClass = [%bs.raw {| css(tw`
  h-4
`)|}];

let make = (_children) => {
  ...component,
  render: _self =>
    <div className=mainPageContentHomeClass>
      <div className=(backgroundImageClass ++ " bg-image") />
      <div className=aboutUsSubscriptionClass>
        {ReasonReact.string("abcdefg")}
      </div>
    </div>
};