let component = ReasonReact.statelessComponent("MainPageContentSubscribeContainer");

let css = Css.css;
let tw = Css.tw;

let mainPageContentSubscribeClass = [%bs.raw {| css(tw`
`)|}];

let make = (_children) => {
  ...component,
  render: _self =>
    <div className=mainPageContentSubscribeClass>
      {(ReasonReact.string("Subscribe"))}
    </div>
};