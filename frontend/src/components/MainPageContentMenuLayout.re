
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
    | SelectDiet(_selectedDiet) => ReasonReact.NoUpdate
    | EditRestriction(changedRestrictionId, selected) => {
      Js.log("changedRestrictionId");
      Js.log(changedRestrictionId);

      Js.log("state.restrictions");
      Js.log(state.restrictions);

      Js.log("selected");
      Js.log(selected);
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