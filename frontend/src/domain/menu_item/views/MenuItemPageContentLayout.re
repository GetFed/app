
let css = Css.css;
let tw = Css.tw;

let menuItemContentClass = [%bs.raw {| css(tw`
  sm:mx-4
`)|}];
let menuItemLayoutWrapperImageClass = [%bs.raw {| css(tw`
  w-full
  sm:block
  sm:h-auto
  mb-4
`)|}];

let menuItemLayoutImageClass = [%bs.raw {| css(tw`
  w-full
`)|}];

let menuItemLayoutNameClass = [%bs.raw {| css(tw`
  text-green-darker
  text-3xl
  flex
  justify-center
  mb-4
`)|}];


let menuItemLayoutDescriptionClass = [%bs.raw {| css(tw`
  flex
  justify-center
  mb-4
`)|}];

let menuItemLayoutButtonClass = [%bs.raw {| css(tw`
  flex
  justify-center
  mb-4
`)|}];

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


let component = ReasonReact.statelessComponent("MenuItemPageContentLayout");

let make = (~data as menuItem : MenuItem.Model.Record.t, _children) => {
  ...component,
  render: _self =>
    {
      <div className=menuItemContentClass>
        <div className=menuItemLayoutWrapperImageClass>
          <img className=(menuItemLayoutImageClass ++ " object-contain") src=(Utils.Fed.legacyFedUrl(menuItem.data.photo)) />
        </div>
        <div className=menuItemLayoutNameClass>
          {ReasonReact.string(menuItem.data.name)}
        </div>
        <div className=menuItemLayoutDescriptionClass>
          {ReasonReact.string(menuItem.data.description)}
        </div>
        <div className=menuItemLayoutButtonClass>
          <ItemCartAddButtons />
        </div>
        {
          menuItem.data.productId
          |> FoodProduct.Container.getRecordById
          |> Belt.Option.mapWithDefault(_, <div/>, (foodProduct) => {
            foodProduct.data.foodId
            |> Food.Container.getRecordById
            |> Belt.Option.mapWithDefault(_, <div/>, (food) => {
              <FoodAttributesLayout data=food />
            })
          })
        }
      </div>
    }
};