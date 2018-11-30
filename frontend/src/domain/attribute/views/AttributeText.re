let component = ReasonReact.statelessComponent("AttributeText");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
let attributeTextClass = [%bs.raw {| css(tw`
`)|}];

let make = (~data as attribute : Attribute.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div className=attributeTextClass>
      {ReasonReact.string(attribute.data.name)}
    </div>,
};