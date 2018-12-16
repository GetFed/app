let component = ReasonReact.statelessComponent("IngredientText");

let css = Css.css;
let tw = Css.tw;
let ingredientTextClass = [%bs.raw {| css(tw`
  pr-1
`)|}];


let make = (~data as ingredient : IngredientBaseSpread.Model.Record.t, _children) => {
  ...component,
  render: _self => {
    <div className=ingredientTextClass>
      {ReasonReact.string("*" ++ ingredient.data.name ++ ", ")}
    </div>
  },
};