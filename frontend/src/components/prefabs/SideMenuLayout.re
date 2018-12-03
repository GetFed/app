let component = ReasonReact.statelessComponent("SideMenuLayout");

let css = Css.css;
let tw = Css.tw;

let sidemenuLayoutClass = [%bs.raw {| css(tw`
  flex
  flex-wrap
  relative
`)|}];

let sidemenuContentsClass = [%bs.raw {| css(tw`
  
  w-full
  sm:w-3/4
  md:w-5/6
`)|}];

let sidemenuClass = [%bs.raw {| css(tw`
  hidden
  sm:block

  w-full
  sm:w-1/4
  md:w-1/6

  h-screen
  z-10
  fixed
  overflow-y-auto
  `)|}];

let sidemenuEmptyClass = [%bs.raw {| css(tw`
  w-full
  sm:w-1/4
  md:w-1/6
`)|}];

let make =
    (~sideMenu, children) => {
  ...component,
  render: _self =>
    <div>
      <div className=sidemenuClass>
        {sideMenu}
      </div>
      <div key="sidemenuLayout" className=sidemenuLayoutClass>
        <div className=sidemenuEmptyClass />
        <div className=sidemenuContentsClass>
          (children |> ReasonReact.array)
        </div>
      </div>
    </div>,
};