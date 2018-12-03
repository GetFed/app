let component = ReasonReact.statelessComponent("FedButton");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let dietButtonClass = [%bs.raw {| css(tw`
  bg-green-darker
  hover:bg-green-darkest
  text-white
  py-1
  px-4
  rounded-lg
  text-lg
  w-full
`)|}];

let colorClassGreen = [%bs.raw {| css(tw`
  bg-green-darker
`)|}];

let colorClassGrey = [%bs.raw {| css(tw`
  bg-grey-darker
`)|}];

type color =
  | GREEN
  | GREY;

let colorClass = (color : color) =>
  switch(color) {
  | GREEN => colorClassGreen
  | GREY => colorClassGrey
  };

let make = (~onClick, ~color=GREEN, children) => {
  ...component,
  render: _self =>
   <button className=cx(dietButtonClass, colorClass(color)) onClick>
     {children |> ReasonReact.array}
   </button>
};