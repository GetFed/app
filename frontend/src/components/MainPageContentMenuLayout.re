
let css = Css.css;
let tw = Css.tw;

let mainPageContentFedFilterClass = [%bs.raw {| css(tw`
  mb-4
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
    | EditRestriction(_restrictionId, _selected) => ReasonReact.NoUpdate
    | Noop => ReasonReact.NoUpdate
    },
  render: self =>
    <div>
      <div className=mainPageContentFedFilterClass>
        <FedFilter diets selectedDietId=self.state.selectedDietId />
      </div>
      <FedMenuSection restrictions/>
    </div>
};