let component = ReasonReact.statelessComponent("FoodAttributesLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let menuItemAttributesClass = [%bs.raw {| css(tw`
  flex
  justify-center
  mb-4
`)|}];

let menuItemTextSpaceClass = [%bs.raw {| css(tw`
  mx-2
`)|}];

let menuItemRestrictionClass = [%bs.raw {| css(tw`
  flex
  justify-center
`)|}];

      
let make = (~data as food : Food.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    <div>
      <div className=menuItemAttributesClass>
      {
        food.data.attributeIds
        |> Utils.List.removeOptionsFromList
        |> Belt.List.map(_, Attribute.Container.getRecordById)
        |> Utils.List.removeOptionsFromList
        |> Belt.List.map(_, (attribute) =>
            <div className=menuItemTextSpaceClass><AttributeText data=attribute/></div>)
        |> Utils.ReasonReact.listToReactArray
      }
    </div>
    {
      food.data.restrictionIds
      |> Belt.Option.mapWithDefault(_, <div />, (restrictionIds) =>
          <div className=menuItemRestrictionClass>
            {ReasonReact.string("CONTAINS: ")}
            {
              restrictionIds
              |> Utils.List.removeOptionsFromList
              |> Belt.List.map(_, Restriction.Container.getRecordById)
              |> Utils.List.removeOptionsFromList
              |> Belt.List.map(_, (restriction) => 
                  <div className=menuItemTextSpaceClass><RestrictionText data=restriction/></div>)
              |> Utils.ReasonReact.listToReactArray
            }
          </div>
        )
    }
    {
      food.data.nutritionFactsId
      |> NutritionFacts.Container.getRecordById
      |> Belt.Option.mapWithDefault(_, <div />, (nutritionFacts) =>
          <NutritionFactLayout data=nutritionFacts />
      )
    }
  </div>,
};