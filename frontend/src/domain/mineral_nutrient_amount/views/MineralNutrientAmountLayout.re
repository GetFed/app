let component = ReasonReact.statelessComponent("MineralNutrientAmountLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
let macroNutrientAmountClass = [%bs.raw {| css(tw`
  pl-2
`)|}];

let make = (~data as mineralNutrientAmount : MineralNutrientAmount.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div className=macroNutrientAmountClass>
      {ReasonReact.string(mineralNutrientAmount.data.name ++ " ")}
      {ReasonReact.string(mineralNutrientAmount.data.percentageDailyValue |> Utils.String.nutritionPrecision)}
      {ReasonReact.string("%, ")}
    </div>,
};