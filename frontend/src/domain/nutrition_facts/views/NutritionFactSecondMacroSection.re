let component = ReasonReact.statelessComponent("NutritionFactSecondMacroSection");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let generateMacroNutrientAmount = (macroNutrientAmountId, major: bool) =>
  macroNutrientAmountId
  |> MacroNutrientAmount.Container.getRecordById
  |> Belt.Option.mapWithDefault(_, <div />,
      (macroNutrientAmount) => <MacroNutrientAmountLayout data=macroNutrientAmount major=major />)

let nutritionFactSecondMacroSectionClass = [%bs.raw {| css(tw`
  px-1
`)|}];
let nutritionHeaderSeparatorClass = [%bs.raw {| css(tw`
  border-0
  border-b-4
  border-black
  border-solid
`)|}];

let nutritionFactSeparatorClass = [%bs.raw {| css(tw`
  border-0
  border-b-2
  border-black
  border-solid
`)|}];

let make = (~data as nutritionFacts : NutritionFacts.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div className=nutritionFactSecondMacroSectionClass>
      <div className=nutritionHeaderSeparatorClass>
        <AmountServingHeader />
      </div>
      <div className=nutritionFactSeparatorClass>
        {generateMacroNutrientAmount(nutritionFacts.data.totalFatId, true)}
      </div>
      <div className=nutritionFactSeparatorClass>
        {generateMacroNutrientAmount(nutritionFacts.data.saturatedFatId, false)}
      </div>
      {
        nutritionFacts.data.transFatId
        |> Belt.Option.mapWithDefault(_, <div/>, (id) => {
          <div className=nutritionFactSeparatorClass>
            {generateMacroNutrientAmount(id, false)}
          </div>
        })
      }
      <div className=nutritionFactSeparatorClass>
        {generateMacroNutrientAmount(nutritionFacts.data.cholesterolId, true)}
      </div>
      <div className=nutritionFactSeparatorClass>
        {generateMacroNutrientAmount(nutritionFacts.data.sodiumId, true)}
      </div>
    </div>
};