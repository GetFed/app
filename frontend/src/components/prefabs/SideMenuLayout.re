let css = Css.css;
let cx = Css.cx;
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

let sidemenuTopContentClass = [%bs.raw {| css(tw`
  fixed
  w-full
  flex
  h-16
  sm:hidden
  z-30
  bg-white
`)|}];

let sidemenuRealContentsClass = [%bs.raw {| css(tw`
  mt-16
  sm:mt-0
`)|}];

let openedSideMenuClass = [%bs.raw {| css(tw`
  w-1/2
  block
  bg-white
  mt-16
`)|}];

let sidemenuContentBackgroundClass = [%bs.raw {| css(tw`
  z-0
`)|}];

let hamburgerWrapperClass = [%bs.raw {| css(tw`
  h-full
  w-16
  flex
  justify-center
  items-center
  cursor-pointer
`)|}];

let hamburgerClass = [%bs.raw {| css(tw`
  w-8
  h-8
  text-green-darker
`)|}];

type state = {
  openTopMenu: bool
};

type action =
  | ToggleMenu;

let defaultState = {
  openTopMenu: false
};

let component = ReasonReact.reducerComponent("SideMenuLayout");

let make = (~sideMenu, ~topContent=?, children) => {
  ...component,
  initialState: () => defaultState,
  reducer: (action, state: state) =>
    switch (action) {
    | ToggleMenu => ReasonReact.Update({openTopMenu: !state.openTopMenu})
    },
  render: self =>
    <div>
      <div className=cx(sidemenuClass, self.state.openTopMenu ? openedSideMenuClass : "")>
        {sideMenu}
      </div>
      <div key="sidemenuLayout" className=sidemenuLayoutClass>
        <div className=sidemenuEmptyClass />
        <div className=sidemenuContentsClass>
          <div className=sidemenuTopContentClass>
            <div className=hamburgerWrapperClass onClick=((_) => self.send(ToggleMenu))>
              <BarsIcon className=hamburgerClass />
            </div>
            {Belt.Option.getWithDefault(topContent, <div/>)}
          </div>
          <div className=sidemenuRealContentsClass>
            (children |> ReasonReact.array)
          </div>
        </div>
      </div>
    </div>,
};