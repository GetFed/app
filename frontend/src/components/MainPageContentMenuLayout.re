
let css = Css.css;
let tw = Css.tw;

let mainPageContentFedFilterClass = [%bs.raw {| css(tw`
  mb-4

  hidden
  md:block
`)|}];

type state = {
  selectedDietId: option(Diet.Model.idType),
  restrictions: list(Restriction.Model.idType)
};

type action =
  | SelectDiet(Diet.Model.idType)
  | EditRestriction(Restriction.Model.idType, bool)
  | Noop;

let component = ReasonReact.reducerComponent("MainPageContentMenuLayout");

let make = (~diets, ~restrictions, ~currentMenu, _children) => {
  ...component,
  initialState: () => {
    selectedDietId: Belt.List.head(diets),
    restrictions: [],
  },
  reducer: (_action, state) =>
    switch (_action) {
    | SelectDiet(selectedDiet) => {
        Diet.Container.getRecordById(selectedDiet)
        |> Belt.Option.mapWithDefault(_, ReasonReact.NoUpdate, (diet : Diet.Model.Record.t) => {
          Belt.Option.mapWithDefault(diet.data.restrictionIds, ReasonReact.NoUpdate, (restrictionIds) => {
            ReasonReact.Update({
              restrictions: restrictionIds |> Utils.List.removeOptionsFromList,
              selectedDietId: Some(`DietId(diet.data.id))
            });
          });
        });
      }
    | EditRestriction(changedRestrictionId, selected) => {
      ReasonReact.Update({
        ...state,
        restrictions:
          switch(selected){
          | false =>
              state.restrictions
              |> Belt.List.keep(_, (restrictionId) => restrictionId != changedRestrictionId)
          | true => state.restrictions @ [changedRestrictionId]
          }
      })
    }
    | Noop => ReasonReact.NoUpdate
    },
  render: self =>
    <div>
      <div className=mainPageContentFedFilterClass>
        <FedFilter
          diets
          selectedDietId=self.state.selectedDietId
          restrictions=self.state.restrictions
          updateRestriction=((restrictionId, selected) => self.send(EditRestriction(restrictionId, selected)))
          updateDiet=((dietId) => self.send(SelectDiet(dietId)))
        />
      </div>
      <FedMenuSection restrictions=self.state.restrictions/>
    </div>
};