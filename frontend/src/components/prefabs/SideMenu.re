let component = ReasonReact.statelessComponent("SideMenu");

let css = Css.css;
let tw = Css.tw;
let menuOverlayClass = [%bs.raw {| css(tw`
  w-1/6
  h-screen
  fixed
  
`)|}];

let make =
    (/*~labelContentList: list((string, ReasonReact.reactElement)), */children) => {
  ...component,
  render: _self =>
    <div className=menuOverlayClass>
      {children |> ReasonReact.array}
    </div>,
};