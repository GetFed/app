let component = ReasonReact.statelessComponent("RestrictionChecker");

let css = Css.css;
let tw = Css.tw;

let logoClass = [%bs.raw {| css(tw`
`)|}];

let make = (~data as restriction, _children) => {
  ...component,
  render: _self =>
   <div>
     
   </div>
};