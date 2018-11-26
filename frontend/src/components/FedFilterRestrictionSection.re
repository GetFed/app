let component = ReasonReact.statelessComponent("FedFilterRestrictionSection");

let css = Css.css;
let tw = Css.tw;

let logoClass = [%bs.raw {| css(tw`
`)|}];

let make = (_children) => {
  ...component,
  render: _self =>
  <Query.Restrictions.Container>
  ...{(~restrictions)=> {
    restrictions
    |> Utils.List.removeOptionsFromList(_)
    |> Belt.List.map(_, (restrictionsId) => {
      restrictionsId
      |> Restriction.Container.getRecordById
      |> Belt.Option.map(_, (restriction) => <RestrictionChecker data=restriction/>)
    })
    |> Utils.List.removeOptionsFromList(_)
    |> Utils.ReasonReact.listToReactArray
  }}
  </Query.Restrictions.Container>
};