let component = ReasonReact.statelessComponent("MenuLayout");

let css = Css.css;
let tw = Css.tw;
let menuLayoutClass = [%bs.raw {| css(tw`
  flex
  flex-wrap
  w-full
  h-full
`)|}];

let menuLayoutResonsiveMenuItemClass = [%bs.raw {| css(tw`
  w-full
  sm:w-1/2
  md:w-1/3
  mb-4
`)|}];

let menuLayoutMenuItemClass = [%bs.raw {| css(tw`
  px-2
  h-full
`)|}];


let noMenuItem = <h2>{ReasonReact.string("No current Menu Item")}</h2>;


let make = (~data as menu : Menu.Model.Record.t, ~restrictions: list(Restriction.Model.idType), _children) => {
  ...component,
  render: _self => {
    Js.log("menu.data.itemIds");
    Js.log(menu.data.itemIds);
    <div className=menuLayoutClass>
      {
        menu.data.itemIds
        |> Utils.List.removeOptionsFromList
        |> Belt.List.map(_, (menuItemId) => menuItemId |> MenuItem.Container.getRecordById)
        |> Utils.List.removeOptionsFromList
        |> Belt.List.keep(_, (menuItem) =>
          menuItem.data.productId
          |> FoodProduct.Container.getRecordById
          |> Belt.Option.mapWithDefault(_, true, (foodProduct) =>
            foodProduct.data.foodId
            |> Ingredient.Container.getRecordById
            |> Belt.Option.mapWithDefault(_, true, (ingredient) =>
              ingredient.data.restrictionIds
              |> Belt.Option.mapWithDefault(_, true, (restrictionIds) =>
                !(
                  restrictionIds
                  |> Utils.List.removeOptionsFromList
                  |> Belt.List.some(_, (menuRestrictionId) =>
                    restrictions |> Belt.List.getBy(_, (res) => res == menuRestrictionId) != None
                  )
                )
              )
            )
          )
        )
        |> Belt.List.map(_, (menuItem) =>
          <div key=menuItem.data.id className=menuLayoutResonsiveMenuItemClass>
            <div className=menuLayoutMenuItemClass>
              <MenuItemCardLayout data=menuItem/>
            </div>
          </div>
        )
        |> Utils.ReasonReact.listToReactArray
      }
    </div>
  },
};