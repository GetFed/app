let component = ReasonReact.statelessComponent("AmountServingHeader");

let css = Css.css;
let tw = Css.tw;

let amountServingHeaderClass = [%bs.raw {| css(tw`
  w-full
  flex
  justify-between
`)|}];

let amountServingHeaderTextClass = [%bs.raw {| css(tw`
  font-bold
  text-xs
`)|}];

let make = (_children) => {
  ...component,
  render: _self =>
    <div className=amountServingHeaderClass>
      <div className=amountServingHeaderTextClass>
        {ReasonReact.string("Amount/serving")}
      </div>
      <div className=amountServingHeaderTextClass>
        {ReasonReact.string("% Daily Value*")}
      </div>
    </div>
};