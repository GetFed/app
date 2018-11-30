let component = ReasonReact.statelessComponent("RestrictionText");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
let restrictionText = [%bs.raw {| css(tw`
  text-green-darker
`)|}];

let make = (~data as restriction : Restriction.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div className=restrictionText>
      {ReasonReact.string(restriction.data.name)}
    </div>,
};