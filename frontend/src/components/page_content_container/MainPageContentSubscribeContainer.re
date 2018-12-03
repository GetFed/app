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
  w-full
  text-green-darker
  uppercase
  pb-4
  mb-8
  border-0
  border-b
  border-green-darker
  border-solid
  `)|}];

let make = (_children) => {
  ...component,
  render: _self =>
    <Query.Diets.Container>
      ...{(~diets)=> {
        <Query.Restrictions.Container>
          ...{(~restrictions)=> {
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
          }}
        </Query.Restrictions.Container>
      }}
    </Query.Diets.Container>
    
};