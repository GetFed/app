let component = ReasonReact.statelessComponent("MainPageContentSubscribeContainer");

let css = Css.css;
let tw = Css.tw;

let mainPageContentSubscribeClass = [%bs.raw {| css(tw`
  p-2
`)|}];

let mainPageContentSubscribeSectionClass = [%bs.raw {| css(tw`
  text-green-darker
  mb-12
  `)|}];

let mainPageContentSubscribeSectionTextClass = [%bs.raw {| css(tw`
  w-full
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
`)|}];

let mainPageContentSubscribeRestrictionTextClass = [%bs.raw {| css(tw`
  w-24
`)|}];

let mainPageContentSubscribeButtonClass = [%bs.raw {| css(tw`
  flex
  justify-between
`)|}];

let mainPageContentSubscribeSingleButtonClass = [%bs.raw {| css(tw`
  w-48
`)|}];

let make = (_children) => {
  ...component,
  render: _self =>
    <Query.Diets.Container>
      ...{(~diets)=> {
        <Query.Restrictions.Container>
          ...{(~restrictions)=> {
            let cleanDiets = diets |> Utils.List.removeOptionsFromList;

            <div className=mainPageContentSubscribeClass>
              <div className=mainPageContentSubscribeSectionClass>
                <div className=mainPageContentSubscribeSectionTextClass>
                  {(ReasonReact.string("Edit Your Diet"))}
                </div>
                <div className=mainPageContentSubscribeDietClass>
                  {
                    cleanDiets
                    |> Belt.List.head
                    |> Belt.Option.mapWithDefault(_, <div />, (dietVal) => {
                      <div>
                        <FedFilterDietDropdown
                            diets=cleanDiets
                            selectedDietId=dietVal
                            updateDiet=((dietId) => ())
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
                      selectedRestrictions=(restrictions |> Utils.List.removeOptionsFromList)
                      updateRestriction=((restriction, choice) => ())
                      restrictionClass=mainPageContentSubscribeRestrictionClass
                      restrictionTextClass=mainPageContentSubscribeRestrictionTextClass
                    />
                  }
                </div>
              </div>
              <div className=mainPageContentSubscribeSectionTextClass>
                <div className=mainPageContentSubscribeButtonClass>
                  <div className=mainPageContentSubscribeSingleButtonClass>
                    <FedButton onClick=((_) => ())>
                      {ReasonReact.string("Cancel")}
                    </FedButton>
                  </div>
                  <div className=mainPageContentSubscribeSingleButtonClass>
                    <FedButton onClick=((_) => ())>
                      {ReasonReact.string("Save")}
                    </FedButton>
                  </div>
                </div>
              </div>
            </div>
          }}
        </Query.Restrictions.Container>
      }}
    </Query.Diets.Container>
    
};