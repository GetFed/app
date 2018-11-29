let component = ReasonReact.statelessComponent("MenuItemLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
let menuItemLayoutClass = [%bs.raw {| css(tw`
  max-w-sm
  overflow-hidden
  shadow-lg
  flex
  h-full


  
  sm:flex-col
`)|}];


let menuItemLayoutWrapperImageClass = [%bs.raw {| css(tw`
  sm:w-full
  sm:block
  
  w-1/3


  h-full
  sm:h-auto
  
  
`)|}];

let menuItemLayoutImageClass = [%bs.raw {| css(tw`
  w-full
`)|}];

let menuItemSecondSectionClass = [%bs.raw {| css(tw`
  sm:w-full
  w-2/3
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

let menuItemLayoutButtonClass = [%bs.raw {| css(tw`
  text-green-darker
  bg-grey
  font-bold
  px-2
  border-b-4
  text-xl
  rounded
  `)|}];

let menuItemLayoutCountClass = [%bs.raw {| css(tw`
  mx-4
  flex
  justify-center
  items-center
`)|}];

let menuItemLayoutButtonsClass = [%bs.raw {| css(tw`
  flex
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
      <div className=menuItemLayoutWrapperImageClass>
        <img className=(menuItemLayoutImageClass ++ " object-contain") src=(Utils.Fed.legacyFedUrl(menuItem.data.photo)) />
      </div>
      <div className=menuItemSecondSectionClass>
        <div className=menuItemLayoutContentClass>
          <div className=cx(menuItemLayoutNameClass, menuItemLayouteContentDescriptionSection)>
            {ReasonReact.string(menuItem.data.name)}
          </div>
          <div className=cx(menuItemLayoutDescriptionClass, menuItemLayouteContentDescriptionSection)>
            {ReasonReact.string(menuItem.data.description)}
          </div>
          <div className=cx(menuItemLayoutFooterClass, menuItemLayouteContentDescriptionSection)>
            <div className=menuItemLayoutPriceClass>
              {menuItem.data.price |> Utils.String.toMoney |> ((s) => "$" ++ s) |> ReasonReact.string}
            </div>
            <div className=menuItemLayoutButtonsClass>
              <button className=menuItemLayoutButtonClass>{ReasonReact.string("-")}</button>
              <div className=menuItemLayoutCountClass>{numberInCart |> string_of_int |> ReasonReact.string}</div>
              <button className=menuItemLayoutButtonClass>{ReasonReact.string("+")}</button>
            </div>
          </div>
        </div>
      </div>
    </div>,
};