let component = ReasonReact.statelessComponent("MainPageContentHomeContainer");

let css = Css.css;
let tw = Css.tw;

let mainPageContentHomeClass = [%bs.raw {| css(tw`
  w-screen
  absolute
  pin-t
  pin-l
`)|}];

let backgroundImageClass = [%bs.raw {| css(tw`
  w-full
  h-screen
  bg-cover
  bg-center
  flex
`)|}];

let aboutUsSubscriptionClass = [%bs.raw {| css(tw`
  h-4
`)|}];

let mainPageContentHomeEmptySpaceClass = [%bs.raw {| css(tw`
  w-1/4
`)|}];

let mainPageContentHomeMiddleAreaClass = [%bs.raw {| css(tw`
  w-1/2
`)|}];

let mainPageContentHomeTextAreaClass = [%bs.raw {| css(tw`
  pl-4
  pt-16
`)|}];

/* let mainPageContentHomeShadyAreaClass = [%bs.raw {| css(tw`
  h-16
  w-16
`)|}]; */

let mainPageContentHomeTextEatEverydayClass = [%bs.raw {| css(tw`
  text-white
  text-5xl
  mb-8
`)|}];

let mainPageContentHomeTextGourmetClass = [%bs.raw {| css(tw`
  text-white
  text-2xl
`)|}];

let make = (_children) => {
  ...component,
  render: _self =>
    <div className=mainPageContentHomeClass>
      
      <div className=(backgroundImageClass ++ " bg-image")>
        <div className=mainPageContentHomeEmptySpaceClass/>
        <div className=mainPageContentHomeMiddleAreaClass>
        <div className=mainPageContentHomeTextAreaClass>
          <div className=mainPageContentHomeTextEatEverydayClass>
            <div className="text-shadow">
              {ReasonReact.string("Eat Well, ")}
            </div>
            <div className="text-shadow">
              {ReasonReact.string("Everyday")}
            </div>
          </div>
          </div>
          <div className=mainPageContentHomeTextAreaClass>
          <div className=mainPageContentHomeTextGourmetClass>
            <div className="text-shadow">
              {ReasonReact.string("Gourmet meal plans")}
            </div>
            <div className="text-shadow">
              {ReasonReact.string("fit for every lifestyle")}
            </div>
            </div>
          </div>
        </div>
        <div className=mainPageContentHomeEmptySpaceClass/>
      </div>
    </div>
};