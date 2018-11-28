let component = ReasonReact.statelessComponent("FedFilterRestrictionSection");

let css = Css.css;
let tw = Css.tw;

let fedFilterRestrictionSectionClass = [%bs.raw {| css(tw`
  flex
  h-full
`)|}];

let fedFilterRestrictionSectionItemClass = [%bs.raw {| css(tw`
  max-h-full
  w-10
  mx-2
`)|}];

let make = (
  ~selectedRestrictions: list(Restriction.Model.idType),
  ~updateRestriction: ((Restriction.Model.idType, bool) => unit),
  _children
) => {
  ...component,
  render: _self => {
    <Query.Restrictions.Container>
      ...{(~restrictions)=> {
        <div className=fedFilterRestrictionSectionClass>
          {
            restrictions
            |> Utils.List.removeOptionsFromList(_)
            |> Belt.List.map(_, (restrictionsId) => {
              restrictionsId
              |> Restriction.Container.getRecordById
              |> Belt.Option.map(_, (restriction) => 
                <div className=fedFilterRestrictionSectionItemClass>
                  <RestrictionChecker
                    data=restriction
                    updateRestriction
                    restricted=(
                      Belt.List.getBy(selectedRestrictions, (id) => id == `RestrictionId(restriction.data.id)) != None
                    )
                  />
                </div>
              )
            })
            |> Utils.List.removeOptionsFromList(_)
            |> Utils.ReasonReact.listToReactArray
          }
        </div>
      }}
    </Query.Restrictions.Container>
  }
};