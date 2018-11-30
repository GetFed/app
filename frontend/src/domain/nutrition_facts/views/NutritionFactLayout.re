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
        <div>{ReasonReact.string("Calories ")}</div>
        {ReasonReact.string(
          Utils.String.nutritionPrecision(nutritionFacts.data.calories)
        )}
      </div>
      {
        nutritionFacts.data.caloriesFromFat
        |> Belt.Option.mapWithDefault(_, <div/>, (caloriesFromFat) => {
          <div>
            <div>{ReasonReact.string("Calories from Fat")}</div>
            {
              ReasonReact.string(
                Utils.String.nutritionPrecision(caloriesFromFat)
              )
            }
          </div>
        })
      }
      /* <div>
        <div>{ReasonReact.string("Total Fat ")}</div>
        {
          nutritionFacts.data.totalFat
        }
      </div> */
      
    </div>,
};