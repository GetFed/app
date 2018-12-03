let component = ReasonReact.statelessComponent("NutritionFactThirdMacroSection");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
let generateMacroNutrientAmount = (macroNutrientAmountId, major: bool) =>
  macroNutrientAmountId
  |> MacroNutrientAmount.Container.getRecordById
  |> Belt.Option.mapWithDefault(_, <div />,
      (macroNutrientAmount) => <MacroNutrientAmountLayout data=macroNutrientAmount major=major />)

let nutritionFactThirdMacroSectionClass = [%bs.raw {| css(tw`
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
    <div className=nutritionFactThirdMacroSectionClass>
      <div className=nutritionHeaderSeparatorClass>
        <AmountServingHeader />
      </div>
      <div className=nutritionFactSeparatorClass>
        {generateMacroNutrientAmount(nutritionFacts.data.totalCarbohydrateId, true)}
      </div>
      {
        nutritionFacts.data.dietaryFiberId
        |> Belt.Option.mapWithDefault(_, <div/>, (id) => {
          <div className=nutritionFactSeparatorClass>
            {generateMacroNutrientAmount(id, false)}
          </div>
        })
      }
      <div className=nutritionFactSeparatorClass>
        {generateMacroNutrientAmount(nutritionFacts.data.sugarId, false)}
      </div>
      <div className=nutritionFactSeparatorClass>
        {generateMacroNutrientAmount(nutritionFacts.data.addedSugarId, false)}
      </div>
      <div className=nutritionFactSeparatorClass>
        {generateMacroNutrientAmount(nutritionFacts.data.proteinId, true)}
      </div>
    </div>
};