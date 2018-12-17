let component = ReasonReact.statelessComponent("FedFilterSelection");

let css = Css.css;
let tw = Css.tw;

let mainPageContentSubscribeClass = [%bs.raw {| css(tw`
  p-2
  pt-8
  bg-white
  w-full
  h-full
  md:w-3/4
  md:h-5/6
`)|}];

let mainPageContentSubscribeSectionClass = [%bs.raw {| css(tw`
  text-green-darker
  mb-12
  w-full
  px-12
  `)|}];

let mainPageContentSubscribeSectionTextClass = [%bs.raw {| css(tw`
  w-full
  text-xl
  text-green-darker
  uppercase
  pb-3
  mb-8
  border-0
  border-b
  border-green-darker
  border-solid
  `)|}];

let mainPageContentSubscribeDietClass = [%bs.raw {| css(tw`
  w-full
  flex
  justify-center
  mb-4
  
`)|}];

let mainPageContentSubscribeRestrictionClass = [%bs.raw {| css(tw`
  h-24
  md:h-32
`)|}];

let mainPageContentSubscribeRestrictionTextClass = [%bs.raw {| css(tw`
  w-24
  md:w-32
`)|}];

let mainPageContentSubscribeButtonClass = [%bs.raw {| css(tw`
  flex
  justify-around
  flex-wrap
`)|}];

let mainPageContentSubscribeSingleButtonClass = [%bs.raw {| css(tw`
  w-48
`)|}];

let make = (
  ~restrictions:list(Restriction.Model.idType),
  ~diets: list(Diet.Model.idType),
  ~selectedDietId: option(Diet.Model.idType),
  ~updateRestriction: ((Restriction.Model.idType, bool) => unit),
  ~updateDiet: ((Diet.Model.idType) => unit),
  ~onCancel: option(ReactEventRe.Mouse.t => unit)=?,
  ~onSave: ReactEventRe.Mouse.t => unit,
  ~size=FedButton.LARGE,
  ~color=FedButton.GREY,
  _children
) => {
  ...component,
  render: _self => {
    <div className=mainPageContentSubscribeClass>
      <div className=mainPageContentSubscribeSectionClass>
        <div className=mainPageContentSubscribeSectionTextClass>
          {(ReasonReact.string("Edit Your Diet"))}
        </div>
        <div className=mainPageContentSubscribeDietClass>
          {
            diets
            |> Belt.List.head
            |> Belt.Option.mapWithDefault(_, <div />, (dietVal) => {
              <div>
                <FedFilterDietDropdown
                  diets=diets
                  selectedDietId=dietVal
                  updateDiet
                  size
                  color
                />
              </div>
            })
          }
        </div>
      </div>
      <div className=mainPageContentSubscribeSectionClass>
        <div className=mainPageContentSubscribeSectionTextClass>
          {(ReasonReact.string("Add Restrictions"))}
        </div>
        <div className=mainPageContentSubscribeDietClass>
          {
            <FedFilterRestrictionSection
              selectedRestrictions=restrictions
              updateRestriction
              restrictionClass=mainPageContentSubscribeRestrictionClass
              restrictionTextClass=mainPageContentSubscribeRestrictionTextClass
            />
          }
        </div>
      </div>
      <div className=mainPageContentSubscribeSectionTextClass>
        <div className=mainPageContentSubscribeButtonClass>
          {
            [
              Belt.Option.map(onCancel, (onCancel) =>{
                <div className=mainPageContentSubscribeSingleButtonClass>
                  <FedButton onClick=onCancel>
                    {ReasonReact.string("Cancel")}
                  </FedButton>
                </div>
              }),
              Some(
                <div className=mainPageContentSubscribeSingleButtonClass>
                  <FedButton onClick=onSave>
                    {ReasonReact.string("Save")}
                  </FedButton>
                </div>
              )
            ]
            |> Utils.List.removeOptionsFromList
            |> Belt.List.toArray
            |> ReasonReact.array
          }
          
        </div>
      </div>
    </div>
  }
};