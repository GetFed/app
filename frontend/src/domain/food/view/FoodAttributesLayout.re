let component = ReasonReact.statelessComponent("FoodAttributesLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let foodAttributesLayoutClass = [%bs.raw {| css(tw`
  flex
  justify-center
  mb-4
`)|}];

let foodAttributesLayoutTextSpaceClass = [%bs.raw {| css(tw`
  mx-2
  flex
`)|}];

let foodAttributesLayoutNutritionalFactsClass = [%bs.raw {| css(tw`
  mb-8
`)|}];

let make = (~data as food : Food.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div>
      <div className=foodAttributesLayoutClass>
        {
          food.data.attributeIds
          |> Utils.List.removeOptionsFromList
          |> Belt.List.map(_, Attribute.Container.getRecordById)
          |> Utils.List.removeOptionsFromList
          |> Belt.List.map(_, (attribute) =>
              <div className=foodAttributesLayoutTextSpaceClass><AttributeText data=attribute/></div>)
          |> Utils.ReasonReact.listToReactArray
        }
      </div>
      <div className=foodAttributesLayoutClass>
        {
          food.data.restrictionIds
          |> Belt.Option.mapWithDefault(_, <div />, (restrictionIds) =>
              <div className=foodAttributesLayoutTextSpaceClass>
                {ReasonReact.string("CONTAINS: ")}
                {
                  restrictionIds
                  |> Utils.List.removeOptionsFromList
                  |> Belt.List.map(_, Restriction.Container.getRecordById)
                  |> Utils.List.removeOptionsFromList
                  |> Belt.List.map(_, (restriction) => 
                      <div className=foodAttributesLayoutTextSpaceClass><RestrictionText data=restriction/></div>)
                  |> Utils.ReasonReact.listToReactArray
                }
              </div>
            )
        }
      </div>
      <div className=foodAttributesLayoutNutritionalFactsClass>
        {
          food.data.nutritionFactsId
          |> NutritionFacts.Container.getRecordById
          |> Belt.Option.mapWithDefault(_, <div />, (nutritionFacts) =>
              <NutritionFactLayout data=nutritionFacts />
          )
        }
      </div>
      <div>
        {
          food.data.ingredientIds
          |> Utils.List.removeOptionsFromList
          |> Belt.List.map(_, Ingredient.Container.getRecordById)
          |> Utils.List.removeOptionsFromList
          |> Belt.List.map(_, (ingredient) => <IngredientText data=ingredient />)
          |> Utils.ReasonReact.listToReactArray
        }
      </div>
    </div>,
};