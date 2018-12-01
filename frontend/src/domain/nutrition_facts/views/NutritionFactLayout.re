let component = ReasonReact.statelessComponent("NutritionFactLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
let nutritionFactLayoutClass = [%bs.raw {| css(tw`
`)|}];

let generateMacroNutrientAmount = (macroNutrientAmountId) =>
  macroNutrientAmountId
  |> MacroNutrientAmount.Container.getRecordById
  |> Belt.Option.mapWithDefault(_, <div />,
      (macroNutrientAmount) => <MacroNutrientAmountLayout data=macroNutrientAmount />)

let make = (~data as nutritionFacts : NutritionFacts.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div className=nutritionFactLayoutClass>
      <div>{ReasonReact.string("Nutrition Facts")}</div>
      <div>
        {ReasonReact.string(
          "Serving Size "
          ++ Utils.String.nutritionPrecision(nutritionFacts.data.servingSize) ++
          "g"
          )
        }
      </div>
      <div>
        {ReasonReact.string(
          "Servings Per Container "
          ++ Utils.String.nutritionPrecision(nutritionFacts.data.servingsPerContainer)
          ++ "g"
        )}
      </div>
      <div>
        <div>{ReasonReact.string("Calories: ")}</div>
        {ReasonReact.string(
          Utils.String.nutritionPrecision(nutritionFacts.data.calories)
        )}
      </div>
      {
        nutritionFacts.data.caloriesFromFat
        |> Belt.Option.mapWithDefault(_, <div/>, (caloriesFromFat) => {
          <div>
            <div>{ReasonReact.string("Calories from Fat: ")}</div>
            {
              ReasonReact.string(Utils.String.nutritionPrecision(caloriesFromFat))
            }
          </div>
        })
      }
      <div>
        <div>{ReasonReact.string("Total Fat ")}</div>
        {generateMacroNutrientAmount(nutritionFacts.data.totalFatId)}
      </div>
      <div>
        <div>{ReasonReact.string("Saturated Fat ")}</div>
        {generateMacroNutrientAmount(nutritionFacts.data.totalFatId)}
      </div>
      {
        nutritionFacts.data.transFatId
        |> Belt.Option.mapWithDefault(_, <div/>, (id) => {
          <div>
            <div>{ReasonReact.string("Trans Fat ")}</div>
            {generateMacroNutrientAmount(id)}
          </div>
        })
      }
      <div>
        <div>{ReasonReact.string("Cholesterol ")}</div>
        {generateMacroNutrientAmount(nutritionFacts.data.cholesterolId)}
      </div>
      <div>
        <div>{ReasonReact.string("Sodium ")}</div>
        {generateMacroNutrientAmount(nutritionFacts.data.sodiumId)}
      </div>
      <div>
        <div>{ReasonReact.string("Total Carbohydrates ")}</div>
        {generateMacroNutrientAmount(nutritionFacts.data.totalCarbohydrateId)}
      </div>
      {
        nutritionFacts.data.dietaryFiberId
        |> Belt.Option.mapWithDefault(_, <div/>, (id) => {
          <div>
            <div>{ReasonReact.string("Dietary Fiber ")}</div>
            {generateMacroNutrientAmount(id)}
          </div>
        })
      }
      <div>
        <div>{ReasonReact.string("Total Sugar ")}</div>
        {generateMacroNutrientAmount(nutritionFacts.data.sugarId)}
      </div>
      <div>
        <div>{ReasonReact.string("Protein ")}</div>
        {generateMacroNutrientAmount(nutritionFacts.data.proteinId)}
      </div>
      <div>
        {
          nutritionFacts.data.mineralIds
          |> Utils.List.removeOptionsFromList
          |> Belt.List.map(_, (mineralId) => {
            mineralId
            |> MineralNutrientAmount.Container.getRecordById
            |> Belt.Option.mapWithDefault(_, <div />,
                (amount) => <MineralNutrientAmountLayout data=amount />)
          })
          |> Utils.ReasonReact.listToReactArray
        }
      </div>
    </div>,
};