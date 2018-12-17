let component = ReasonReact.statelessComponent("Modal");

let css = Css.css;
let tw = Css.tw;

let modalOverlayClass = [%bs.raw
  {| css(tw`
  fixed
  h-screen
  w-screen
  bg-grey-darkest
  opacity-50
  z-40
`)
|}
];

let modalOuterClass = [%bs.raw
  {| css(tw`
  fixed
  w-screen
  h-screen
  z-50
  flex
  justify-center
  items-center
`)
|}
];

let make =
    (
      ~modalSelect: option('a),
      ~modalContents: 'a => ReasonReact.reactElement,
      ~closeFn: unit => unit,
      children,
    ) => {
  ...component,
  render: _self =>
    <div>
      {
        switch (modalSelect) {
        | Some(select) =>
          <div >
            <div className=modalOverlayClass onClick=(_ => closeFn() |> ignore) />
            <div
              className=modalOuterClass
              onClick=(
                e => {
                  let currentTarget = ReactEventRe.Mouse.currentTarget(e);
                  let target = ReactEventRe.Mouse.target(e);
                  let isSameElement = (target == currentTarget);
                  (isSameElement ? closeFn() : ())
                }
              )
            >
              {select |> modalContents}
            </div>
          </div>
        | _ => <div />
        }
      }
      {ReasonReact.createDomElement("div", ~props=Js.Obj.empty(), children)}
    </div>,
};