let component = ReasonReact.statelessComponent("SideMenuLayout");

let css = Css.css;
let tw = Css.tw;

let sidemenuLayoutClass = [%bs.raw {| css(tw`
  flex
  flex-wrap
  relative
`)|}];

let sidemenuContentsClass = [%bs.raw {| css(tw`
  w-5/6
  overflow-y-scroll
`)|}];

let sidemenuClass = [%bs.raw {| css(tw`
  w-1/6
  h-screen
  z-10
  overflow-y-scroll
`)|}];

let make =
    (~sideMenu, children) => {
  ...component,
  render: _self =>
    <div key="sidemenuLayout" className=sidemenuLayoutClass>
      <div className=sidemenuClass>
        {sideMenu}
      </div>
      <div className=sidemenuContentsClass>
        (children |> ReasonReact.array)
      </div>
    </div>,
};