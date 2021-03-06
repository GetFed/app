let component = ReasonReact.statelessComponent("MenuItemPageContentLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
let menuItemLayoutClass = [%bs.raw {| css(tw`
  w-full
  overflow-hidden
  shadow-lg
  flex
  sm:flex-col
`)|}];


let menuItemLayoutWrapperImageClass = [%bs.raw {| css(tw`
  sm:w-full
  sm:block
  w-1/2
  h-full
  sm:h-auto
`)|}];

let menuItemLayoutImageClass = [%bs.raw {| css(tw`
  w-full
`)|}];

let menuItemSecondSectionClass = [%bs.raw {| css(tw`
  sm:w-full
  w-1/2
  h-full
`)|}];

let menuItemLayoutContentClass = [%bs.raw {| css(tw`
  h-full
  flex-grow
  flex
  flex-col
  justify-between
  px-4
`)|}];

let menuItemLayouteContentDescriptionSection = [%bs.raw {| css(tw`
  my-2
`)|}];

let menuItemLayoutNameClass = [%bs.raw {| css(tw`
  text-green-darker
  text-lg
`)|}];

let menuItemLayoutDescriptionClass = [%bs.raw {| css(tw`
  text-xs
`)|}];

let menuItemLayoutFooterClass = [%bs.raw {| css(tw`
  text-green-darker
  flex
  justify-between
`)|}];

let menuItemLayoutPriceClass = [%bs.raw {| css(tw`
  flex
  items-center
  text-xl
`)|}];
      
let make = (~data as menuItem : MenuItem.Model.Record.t, ~numberInCart=0, _children) => {
  ...component,
  render: _self =>
    <div className=menuItemLayoutClass>
      <A className=menuItemLayoutWrapperImageClass href=("/menu/" ++ menuItem.data.id)>
        <div key="menuLink" >
          <img className=(menuItemLayoutImageClass ++ " object-contain") src=(Utils.Fed.legacyFedUrl(menuItem.data.photo)) />
        </div>
      </A>
      <div className=menuItemSecondSectionClass>
        <div className=menuItemLayoutContentClass>
          <div className=cx(menuItemLayoutNameClass, menuItemLayouteContentDescriptionSection)>
            <A href=("/menu/" ++ menuItem.data.id)>
              {ReasonReact.string(menuItem.data.name)}
            </A>
          </div>
          <div className=cx(menuItemLayoutDescriptionClass, menuItemLayouteContentDescriptionSection)>
            {ReasonReact.string(menuItem.data.description)}
          </div>
          <div className=cx(menuItemLayoutFooterClass, menuItemLayouteContentDescriptionSection)>
            {
              menuItem.data.productId
              |> FoodProduct.Container.getRecordById
              |> Belt.Option.mapWithDefault(_, <div/>, (foodProduct) => {
                foodProduct.data.productId
                |> ProductBase.Container.getRecordById
                |> Belt.Option.mapWithDefault(_, <div/>, (product) => {
                  <ProductBaseCounterLayout data=product />
                })
              })
            }
          </div>
        </div>
      </div>
    </div>,
};