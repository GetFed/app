let component = ReasonReact.statelessComponent("MainPageContentMenu");

let css = Css.css;
let tw = Css.tw;

let mainPageContentMenuClass = [%bs.raw {| css(tw`
  m-4
`)|}];
let mainPageContentMenuTitleClass = [%bs.raw {| css(tw`
  text-xl
`)|}];

let make = (_children) => {
  ...component,
  render: _self =>
    <div className=mainPageContentMenuClass>
      <h2>{ReasonReact.string("MENU")}</h2>
    </div>,
};