let css = Css.css;
let tw = Css.tw;

let mainPageContentFedFilterClass = [%bs.raw {| css(tw`
  mb-4
`)|}];

type action =
  | Noop;

let component = ReasonReact.statelessComponent("MainPageContentMenuItemContainer");

let make = (~menuItemId: string, _children) => {
  ...component,
  render: _self =>
    <Query.MenuItem.Container id=menuItemId>
      ...{(~menuItem) =>
        menuItem
        |> Belt.Option.mapWithDefault(_, <div />, (menuItem) => {
          menuItem##id
          |> MenuItem.Model.idToTypedId
          |> MenuItem.Container.getRecordById(_)
          |> Belt.Option.mapWithDefault(_, <div />, menuItem => {
            <MenuItemPageContentLayout data=menuItem/>
          })
        })
      }
    </Query.MenuItem.Container>
};