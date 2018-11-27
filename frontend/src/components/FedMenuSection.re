let component = ReasonReact.statelessComponent("FedMenuSection");

let css = Css.css;
let tw = Css.tw;

let noMenu = <h2>{ReasonReact.string("No current Menu")}</h2>;

let mainPageContentMenuClass = [%bs.raw {| css(tw`
  mx-2
`)|}];
let mainPageContentMenuTitleClass = [%bs.raw {| css(tw`
  text-xl
`)|}];

let make = (~restrictions, _children) => {
  ...component,
  render: _self =>
  <div className=mainPageContentMenuClass>
    <Query.CurrentMenu.Container>
      ...{(~currentMenu)=> {
        Belt.Option.mapWithDefault(
          currentMenu,
          noMenu,
          (currentMenu) => {
            `MenuId(currentMenu##id)
            |> Menu.Container.getRecordById
            |> Belt.Option.mapWithDefault(_, noMenu, (menu) => <MenuLayout data=menu/>)
          });
      }}
    </Query.CurrentMenu.Container>
  </div>
};