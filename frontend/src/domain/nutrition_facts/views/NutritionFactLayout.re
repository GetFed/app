let component = ReasonReact.statelessComponent("NutritionFactLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
let nutritionFactLayoutClass = [%bs.raw {| css(tw`
`)|}];

let make = (~data as nutritionFacts : NutritionFacts.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div className=nutritionFactLayoutClass>
      
    </div>,
};