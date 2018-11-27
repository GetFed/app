let component = ReasonReact.statelessComponent("RestrictionChecker");

let css = Css.css;
let tw = Css.tw;

let restrictionCheckerClass = [%bs.raw {| css(tw`
  flex
  flex-col
  h-full
  w-full
`)|}];

let restrictionCheckerImageClass = [%bs.raw {| css(tw`
  h-full
  absolute
`)|}];

let restrictionCheckerImageCrossClass = [%bs.raw {| css(tw`
  absolute
  h-full
  w-full
`)|}];

let restrictionImageAreaClass = [%bs.raw {| css(tw`
  w-full
  relative
  flex
  justify-center
  h-5/6
`)|}];

let restrictionCheckerTextClass = [%bs.raw {| css(tw`
  w-full
  flex
  justify-center
  text-green-darker
  text-xs
  h-1/6
`)|}];

let make = (~data as restriction: Restriction.Model.Record.t, ~restricted: bool=true, _children) => {
  ...component,
  render: _self =>
    <div className=restrictionCheckerClass>
      <div className=restrictionImageAreaClass>
        {
          switch(restriction.data.image){
          | Some(image) => <img className=restrictionCheckerImageClass src=Utils.Fed.legacyFedUrl(image) />
          | None => <div />
          }
        }
        {
          switch(restricted){
          | true =>
              [|
                <img className=restrictionCheckerImageCrossClass src=Utils.Fed.legacyFedUrl("/icons/food/no-line.gif") />,
                <img className=restrictionCheckerImageCrossClass src=Utils.Fed.legacyFedUrl("/icons/food/no-circle.gif") />
              |]
              |> ReasonReact.array
          | false => <div/>
          }
        }
      </div>
      <div className=restrictionCheckerTextClass>
        {ReasonReact.string(restriction.data.id)}
      </div>
    </div>
};