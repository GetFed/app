let component = ReasonReact.statelessComponent("ItemCartAddButtons");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;
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
      
let make = (~numberInCart=0, _children) => {
  ...component,
  render: _self =>
  <div className=menuItemLayoutButtonsClass>
    <button className=menuItemLayoutButtonClass>{ReasonReact.string("-")}</button>
    <div className=menuItemLayoutCountClass>{numberInCart |> string_of_int |> ReasonReact.string}</div>
    <button className=menuItemLayoutButtonClass>{ReasonReact.string("+")}</button>
  </div>,
};



