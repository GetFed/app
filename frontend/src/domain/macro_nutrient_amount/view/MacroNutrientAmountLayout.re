let component = ReasonReact.statelessComponent("MacroNutrientAmountLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
let macroNutrientAmountClass = [%bs.raw {| css(tw`
`)|}];

let make = (~data as macroNutrientAmount : MacroNutrientAmount.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div className=macroNutrientAmountClass>
      {ReasonReact.string(macroNutrientAmount.data.name ++ " ")}
      {ReasonReact.string(macroNutrientAmount.data.amount |> string_of_float)}
    </div>,
};