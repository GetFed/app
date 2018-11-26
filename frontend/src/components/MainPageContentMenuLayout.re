
let css = Css.css;
let tw = Css.tw;

let mainPageContentFedFilterClass = [%bs.raw {| css(tw`
  mb-4
`)|}];

type state = {
  selectedDiet: option(Diet.Model.idType),
};

type action =
  | Noop;

let component = ReasonReact.reducerComponent("MainPageContentMenuLayout");

let make = (~diets, ~restrictions, ~currentMenu, _children) => {
  ...component,
  initialState: () => {
    selectedDiet:
      diets
      |> Belt.List.head
  },
  reducer: (_action, state) =>
    switch (_action) {
    | Noop => ReasonReact.NoUpdate
    },
  render: self =>
    <div>
      <div className=mainPageContentFedFilterClass>
        <FedFilter diets selectedDiet=self.state.selectedDiet />
      </div>
      <FedMenuSection />
    </div>
};