let component = ReasonReact.statelessComponent("MainPageContentSubscribeContainer");

let css = Css.css;
let tw = Css.tw;

let make = (_children) => {
  ...component,
  render: _self =>
    <Query.Diets.Container>
      ...{(~diets)=> {
        <Query.Restrictions.Container>
          ...{(~restrictions)=> {
            <FedFilterSelection
              diets=(diets |> Utils.List.removeOptionsFromList)
              restrictions=(restrictions |> Utils.List.removeOptionsFromList)
              selectedDietId=None
              updateRestriction=((restriction, choice) => ())
              updateDiet=((dietId) => ())
              onCancel=((_) => ())
              onSave=((_) => ())
            />
          }}
        </Query.Restrictions.Container>
      }}
    </Query.Diets.Container>
    
};