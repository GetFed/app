let component = ReasonReact.statelessComponent("SolidOverOpacity");

let css = Css.css;
let tw = Css.tw;
let solidOverOpacityClass = [%bs.raw {| css(tw`
  h-full
  w-full
  relative
`)|}];

let solidOverOpacityOverlayClass = [%bs.raw {| css(tw`
  bg-white
  opacity-50
  h-full
  w-full
  absolute
`)|}];

let solidOverOpacityOverlayContentClass = [%bs.raw {| css(tw`
  h-full
  w-full
  absolute
`)|}];

let make =
    (/*~labelContentList: list((string, ReasonReact.reactElement)), */children) => {
  ...component,
  render: _self =>
    <div className=solidOverOpacityClass>
      <div className=solidOverOpacityOverlayClass/>
      <div className=solidOverOpacityOverlayContentClass>
        {children |> ReasonReact.array}
      </div>
    </div>
};