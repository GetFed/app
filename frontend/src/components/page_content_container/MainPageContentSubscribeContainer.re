let component = ReasonReact.statelessComponent("MainPageContentSubscribeContainer");

let css = Css.css;
let tw = Css.tw;

let mainPageContentSubscribeClass = [%bs.raw {| css(tw`
  p-2
`)|}];

let mainPageContentSubscribeSectionClass = [%bs.raw {| css(tw`
  text-green-darker
  `)|}];

let mainPageContentSubscribeSectionTextClass = [%bs.raw {| css(tw`
  text-green-darker
  uppercase
  underline
  `)|}];

let make = (_children) => {
  ...component,
  render: _self =>
    <div className=mainPageContentSubscribeClass>
      <div className=mainPageContentSubscribeSectionClass>
        <div className=mainPageContentSubscribeSectionTextClass>
          {(ReasonReact.string("Edit Your Diet"))}
        </div>
      </div>
      <div className=mainPageContentSubscribeSectionClass>
        <div className=mainPageContentSubscribeSectionTextClass>
          {(ReasonReact.string("Add Restrictions"))}
        </div>
      </div>
    </div>
};