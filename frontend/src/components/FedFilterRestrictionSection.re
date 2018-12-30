let component = ReasonReact.statelessComponent("FedFilterRestrictionSection");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let fedFilterRestrictionSectionClass = [%bs.raw {| css(tw`
  flex
  flex-wrap
  h-full
  w-full
`)|}];

let fedFilterRestrictionSectionItemClass = [%bs.raw {| css(tw`
  max-h-full
  mx-2
  h-16
`)|}];

let make = (
  ~selectedRestrictions: list(Restriction.Model.idType),
  ~restrictionClass="",
  ~restrictionTextClass="",
  ~updateRestriction: ((Restriction.Model.idType, bool) => unit),
  _children
) => {
  ...component,
  render: _self => {
    <Query.Restrictions.Container>
      ...{(~restrictions)=> {
        <div key="restrictions" className=fedFilterRestrictionSectionClass>
          {
            restrictions
            |> Utils.List.removeOptionsFromList(_)
            |> Belt.List.map(_, (restrictionsId) => {
              restrictionsId
              |> Restriction.Container.getRecordById
              |> Belt.Option.map(_, (restriction) => 
                <div className=cx(fedFilterRestrictionSectionItemClass, restrictionClass)>
                  <RestrictionChecker
                    data=restriction
                    updateRestriction
                    restricted=(
                      Belt.List.getBy(selectedRestrictions, (id) => id == Restriction.Model.idToTypedId(restriction.data.id)) != None
                    )
                    restrictionTextClass
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