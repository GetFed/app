let component = ReasonReact.statelessComponent("ProductBaseCounterLayout");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let productBaseCounterLayoutClass = [%bs.raw {| css(tw`
  flex
  justify-between
  w-full
`)|}];
let menuItemLayoutPriceClass = [%bs.raw {| css(tw`
  flex
  items-center
  text-xl
`)|}];
      
let make = (~data as productBase : ProductBase.Model.Record.t, ~numberInCart=0, _children) => {
  ...component,
  render: _self =>
  <div className=productBaseCounterLayoutClass>
    <div className=menuItemLayoutPriceClass>
      {productBase.data.price |> Utils.String.toMoney |> ((s) => "$" ++ s) |> ReasonReact.string}
    </div>
    <ItemCartAddButtons />
  </div>
};