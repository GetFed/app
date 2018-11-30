
let css = Css.css;
let tw = Css.tw;

let mainPageContentFedFilterClass = [%bs.raw {| css(tw`
  mb-4
`)|}];

type action =
  | Noop;

let component = ReasonReact.statelessComponent("MainPageContentMenuContainer");

let make = (_children) => {
  ...component,
  render: _self =>
  <Query.CurrentMenu.Container>
    ...{(~currentMenu)=> {
      <Query.Diets.Container>
        ...{(~diets)=> {
          <Query.Restrictions.Container>
            ...{(~restrictions)=> {
              <MainPageContentMenuLayout
                key="MainPageContentMenuLayout"
                diets=(diets |> Utils.List.removeOptionsFromList)
                currentMenu
                restrictions=(restrictions |> Utils.List.removeOptionsFromList)
              />
            }}
          </Query.Restrictions.Container>
        }}
      </Query.Diets.Container>
    }}
  </Query.CurrentMenu.Container>
};