let component = ReasonReact.statelessComponent("MainPageContentMyAccount");

let css = Css.css;
let tw = Css.tw;

let make = (_children) => {
  ...component,
  render: _self =>
    <div>
      {ReasonReact.string("CONTENT")}
    </div>,
};