let component = ReasonReact.statelessComponent("MacroNutrientAmountLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
let macroNutrientAmountClass = [%bs.raw {| css(tw`
  w-full
  flex
  justify-between
  py-1
`)|}];

let macroNutrientAmountTextClass = [%bs.raw {| css(tw`
  flex
`)|}];

let macroNutrientAmountNameMajorClass = [%bs.raw {| css(tw`
  font-bold
  pr-2
`)|}];

let macroNutrientAmountNameMinorClass = [%bs.raw {| css(tw`
  ml-6
  pr-2
`)|}];

let make = (~data as macroNutrientAmount : MacroNutrientAmount.Model.Record.t, ~major: bool, _children) => {
  ...component,
  render: _self => {
    let nutrient = macroNutrientAmount.data.nutrientId |> Nutrient.Container.getRecordById;

    <div className=macroNutrientAmountClass>
      <div className=macroNutrientAmountTextClass>
        <div className=(major ? macroNutrientAmountNameMajorClass : macroNutrientAmountNameMinorClass)>
          {ReasonReact.string(macroNutrientAmount.data.name ++ " ")}
        </div>
        {ReasonReact.string(macroNutrientAmount.data.amount |> Utils.String.nutritionPrecision)}
        {
          nutrient
          |> Belt.Option.mapWithDefault(_, <div/>, (nutrient) =>
            nutrient.data.unit
            |> Belt.Option.getWithDefault(_, "")
            |> ReasonReact.string(_))
        }
      </div>
      <div>
        {
          nutrient
          |> Belt.Option.mapWithDefault(_, <div/>, (nutrient) =>
            nutrient.data.recommendedDV
            |> Belt.Option.mapWithDefault(_, <div/>, (dv) =>
              ReasonReact.string(Utils.String.nutritionPrecision((
                (macroNutrientAmount.data.amount /. dv) *. 100.
              )) ++ "%")))
        }
      </div>
    </div>
  }
};