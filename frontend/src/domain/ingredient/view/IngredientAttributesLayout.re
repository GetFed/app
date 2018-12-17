let component = ReasonReact.statelessComponent("IngredientAttributesLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let foodAttributesLayoutClass = [%bs.raw {| css(tw`
  mx-4
`)|}];

let foodAttributesLayoutSectionClass = [%bs.raw {| css(tw`
  flex
  justify-center
  mb-4
`)|}];

let foodAttributesLayoutTextSpaceClass = [%bs.raw {| css(tw`
  mx-2
  flex
`)|}];

let foodAttributesLayoutNutritionalFactsClass = [%bs.raw {| css(tw`
  mb-2
`)|}];

let foodAttributesLayoutIngredientClass = [%bs.raw {| css(tw`
  flex
  flex-wrap
  mb-2
`)|}];

let make = (~data as food : Ingredient.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div className=foodAttributesLayoutClass>
      <div className=foodAttributesLayoutSectionClass>
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
      <div className=foodAttributesLayoutSectionClass>
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
      <div className=foodAttributesLayoutIngredientClass>
        {
          Js.log("food.data.ingredientIds = ");
          Js.log(food.data.ingredientIds);
          food.data.ingredientIds
          |> Utils.List.removeOptionsFromList
          |> Belt.List.map(_, IngredientBaseSpread.Container.getRecordById)
          |> Utils.List.removeOptionsFromList
          |> Belt.List.map(_, (ingredient) => <IngredientText data=ingredient />)
          |> Utils.ReasonReact.listToReactArray
        }
        {ReasonReact.string("*Organic")}
      </div>
    </div>,
};