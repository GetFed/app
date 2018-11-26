let component = ReasonReact.statelessComponent("FedFilterDietSection");

let css = Css.css;
let tw = Css.tw;

let logoClass = [%bs.raw {| css(tw`
`)|}];


let make = (_children) => {
  ...component,
  render: _self =>
  <Query.Diets.Container>
  ...{(~diets)=> {
    diets
    |> Utils.List.removeOptionsFromList(_)
    |> Belt.List.map(_, (dietId) => {
      dietId
      |> Diet.Container.getRecordById
      |> Belt.Option.map(_, (diet) => <DietButton data=diet/>)
    })
    |> Utils.List.removeOptionsFromList(_)
    |> Utils.ReasonReact.listToReactArray
  }}
  </Query.Diets.Container>
};