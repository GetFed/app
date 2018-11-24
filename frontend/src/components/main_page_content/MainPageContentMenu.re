let component = ReasonReact.statelessComponent("MainPageContentMenu");

let css = Css.css;
let tw = Css.tw;

let mainPageContentMenuClass = [%bs.raw {| css(tw`
  m-4
`)|}];
let mainPageContentMenuTitleClass = [%bs.raw {| css(tw`
  text-xl
`)|}];

let noMenu = <h2>{ReasonReact.string("No current Menu")}</h2>;

let make = (_children) => {
  ...component,
  render: _self =>
    <div className=mainPageContentMenuClass>
      <Query.CurrentMenu.Container>
        ...{(~currentMenu)=> {
          Belt.Option.mapWithDefault(
            currentMenu,
            noMenu,
            (currentMenu) => {
              let currentMenuId = currentMenu##id;
              Js.log("currentMenuId");
              Js.log(currentMenuId);
              `MenuId(currentMenuId)
              |> Menu.Container.getRecordById
              |> Belt.Option.mapWithDefault(_, noMenu, (menu) => <MenuLayout data=menu/>)
            });
        }}
      </Query.CurrentMenu.Container>
    </div>,
};