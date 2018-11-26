let component = ReasonReact.statelessComponent("FedFilter");

let css = Css.css;
let tw = Css.tw;

let fedFilterClass = [%bs.raw {| css(tw`
  h-full
  w-full
  bg-grey
`)|}];

let make = (_children) => {
  ...component,
  render: _self =>
   <div className=fedFilterClass>
     <FedFilterDietSection/>
     <FedFilterRestrictionSection/>
   </div>
};