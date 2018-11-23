let component = ReasonReact.statelessComponent("MainPageContentMenu");

let css = Css.css;
let tw = Css.tw;

let mainPageContentMenuClass = [%bs.raw {| css(tw`
  m-4
`)|}];
let mainPageContentMenuTitleClass = [%bs.raw {| css(tw`
  text-xl
`)|}];

let make = (_children) => {
  ...component,
  render: _self =>
    <div className=mainPageContentMenuClass>
      <Query.CurrentMenu.Container>
        ...{(~currentMenu)=> {
          Belt.Option.mapWithDefault(
            currentMenu,
            <h2>{ReasonReact.string("No current Menu")}</h2>,
            (currentMenu) => {
              let currentMenuId = currentMenu##id;
              Js.log("currentMenuId");
              Js.log(currentMenuId);
              <Menu.Container id=currentMenuId>
                ...{(~data) =>
                  <MenuLayout data/>
                }
              </Menu.Container>
            });
        }}
      </Query.CurrentMenu.Container>
    </div>,
};