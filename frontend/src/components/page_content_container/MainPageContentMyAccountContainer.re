let component = ReasonReact.statelessComponent("MainPageContentMyAccountContainer");

let css = Css.css;
let tw = Css.tw;

let make = (_children) => {
  ...component,
  render: _self =>
    <div>
      {ReasonReact.string("MY ACCOUNT")}
    </div>,
};