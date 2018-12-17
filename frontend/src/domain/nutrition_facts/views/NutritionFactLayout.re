let component = ReasonReact.statelessComponent("NutritionFactLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
let nutritionFactLayoutClass = 
  cx(
    [%bs.raw {| css(tw`
      p-2
      border-2
      border-black
      border-solid
      flex
    `)|}],
    [%bs.raw {| css("font-size: .65rem; ")|}]
  );

let nutritionFactLayoutFirstSectionClass = [%bs.raw {| css(tw`
  w-1/6
`)|}];

let nutritionFactLayoutMiddleSectionClass = [%bs.raw {| css(tw`
  w-2/3
  flex
  flex-col
`)|}];

let nutritionFactLayoutRowSectionClass = [%bs.raw {| css(tw`
  flex
  flex-grow
`)|}];

let nutritionFactLayoutThirdSectionClass = [%bs.raw {| css(tw`
  w-1/2
`)|}];

let nutritionFactLayoutSecondSectionClass = [%bs.raw {| css(tw`
  w-1/2
`)|}];

let nutritionFactLayoutThirdSectionClass = [%bs.raw {| css(tw`
  w-1/2
`)|}];

let nutritionFactLayoutFourthSectionClass = [%bs.raw {| css(tw`
  w-1/6
  text-xs
  flex
  flex-col
  justify-center
`)|}];

let nutritionFactSeparatorClass = [%bs.raw {| css(tw`
  border-0
  border-b-2
  border-black
  border-solid
  mb-1
  pb-1
`)|}];

let nutritionFactWordsTextClass = [%bs.raw {| css(tw`
  text-xl
  font-black
`)|}];

let nutritionFactLayoutServingSizeClass = [%bs.raw {| css(tw`
  font-bold
`)|}];

let nutritionFactLayoutCaloriesClass = [%bs.raw {| css(tw`
  font-bold
  flex
`)|}];

let nutritionFactLayoutCaloriesTextClass = [%bs.raw {| css(tw`
`)|}];

let nutritionFactLayoutCaloriesHalfClass = [%bs.raw {| css(tw`
  w-1/2
`)|}];

let nutritionFactLayoutCaloriesCountClass = [%bs.raw {| css(tw`
  flex
  justify-end
`)|}];

let nutritionFactLayoutCaloriesPerServingTextClass = [%bs.raw {| css(tw`
  flex
  justify-end
  text-xs
`)|}];

let nutritionFactLayoutMineralSectionClass = [%bs.raw {| css(tw`
  w-full
  flex
  flex-no-grow
`)|}];

let make = (~data as nutritionFacts : NutritionFacts.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div className=nutritionFactLayoutClass>
      <div className=nutritionFactLayoutFirstSectionClass>
        <div className=nutritionFactSeparatorClass>
          <div className=nutritionFactWordsTextClass>
            {ReasonReact.string("Nutrition")}
          </div>
          <div className=nutritionFactWordsTextClass>
            {ReasonReact.string("Facts")}
          </div>
        </div>
        <div className=nutritionFactSeparatorClass>
          <div>
            {ReasonReact.string(nutritionFacts.data.servingsPerContainer |> Utils.String.nutritionPrecision)}
            {ReasonReact.string(" serving per container")}
          </div>
          <div className=nutritionFactLayoutServingSizeClass>
            {ReasonReact.string(
              "Serving Size ("
              ++ Utils.String.nutritionPrecision(nutritionFacts.data.servingSize) ++
              "g)"
              )
            }
          </div>
        </div>
        <div className=nutritionFactLayoutCaloriesClass>
          <div className=nutritionFactLayoutCaloriesHalfClass>
            <div className=nutritionFactLayoutCaloriesTextClass>{ReasonReact.string("Calories")}</div>
            <div className=nutritionFactLayoutCaloriesPerServingTextClass>{ReasonReact.string("per serving")}</div>
          </div>
          <div className=cx(nutritionFactLayoutCaloriesHalfClass, nutritionFactLayoutCaloriesCountClass)>
            {ReasonReact.string(Utils.String.nutritionPrecision(nutritionFacts.data.calories))}
          </div>
        </div>
      </div>
      <div className=nutritionFactLayoutMiddleSectionClass>
        <div className=nutritionFactLayoutRowSectionClass>
          <div className=nutritionFactLayoutSecondSectionClass>
            <NutritionFactSecondMacroSection data=nutritionFacts />
          </div>
          <div className=nutritionFactLayoutThirdSectionClass>
            <NutritionFactThirdMacroSection data=nutritionFacts />
          </div>
        </div>
        <div className=nutritionFactLayoutMineralSectionClass>
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
      </div>
      <div className=nutritionFactLayoutFourthSectionClass>
        {ReasonReact.string("The % Daily Value (DV) tells you how much a nutrient in a serving of food contributes to a daily diet.  2,000 calories a day is used for general nutrition advice.")}
      </div>
    </div>,
};