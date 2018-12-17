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

let mediumClass = [%bs.raw {| css(tw`
`)|}];

let largeClass = [%bs.raw {| css(tw`
  py-2
  px-6
  text-xl
  `)|}];

type color =
  | GREEN
  | GREY;

type size =
  | MEDIUM
  | LARGE;

let buttonClass = (color : color, size: size) =>
  cx(
    switch(color) {
    | GREEN => colorClassGreen
    | GREY => colorClassGrey
    },
    switch(size) {
    | MEDIUM => mediumClass
    | LARGE => largeClass
    },
  )

let make = (~onClick, ~color=GREEN, ~size=MEDIUM, children) => {
  ...component,
  render: _self =>
   <button className=cx(dietButtonClass, buttonClass(color, size)) onClick>
     {children |> ReasonReact.array}
   </button>
};