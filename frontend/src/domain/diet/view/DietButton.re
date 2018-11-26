let component = ReasonReact.statelessComponent("DietButton");

let css = Css.css;
let tw = Css.tw;

let dietButtonClass = [%bs.raw {| css(tw`
  bg-green-darker
  hover:bg-green-darkest
  text-white
  py-1
  px-4
  rounded-lg
  text-lg
`)|}];

let make = (~data as diet : Diet.Model.Record.t, _children) => {
  ...component,
  render: _self =>
   <button className=dietButtonClass>
     {ReasonReact.string(diet.data.name)}
   </button>
};