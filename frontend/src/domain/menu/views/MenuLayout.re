let component = ReasonReact.statelessComponent("MenuLayout");

let css = Css.css;
let tw = Css.tw;
let menuLayoutClass = [%bs.raw {| css(tw` `)|}];
let make = (~data as menu : Menu.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div className=menuLayoutClass>
      {ReasonReact.string("Menu Id:")}
      {ReasonReact.string(menu.data.id)}
    </div>,
};