let component = ReasonReact.statelessComponent("MenuItemLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
let menuItemLayoutClass = [%bs.raw {| css(tw`
  max-w-sm
  rounded
  overflow-hidden
  shadow-lg
  flex
  flex-col
  h-full
`)|}];
let menuItemLayoutImageClass = [%bs.raw {| css(tw`
  w-full
`)|}];

let menuItemLayoutContentClass = [%bs.raw {| css(tw`
  px-2
  flex-grow
  flex
  flex-col
  justify-between
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
  rounded
  text-xl
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
      <img className=menuItemLayoutImageClass src=("https://getfednyc.com" ++ menuItem.data.photo) />
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
    </div>,
};