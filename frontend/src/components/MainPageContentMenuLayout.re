
let css = Css.css;
let tw = Css.tw;

let mainPageContentFedFilterClass = [%bs.raw {| css(tw`
  mb-4
`)|}];

type state = {
  selectedDietId: option(Diet.Model.idType),
};

type action =
  | Noop;

let component = ReasonReact.reducerComponent("MainPageContentMenuLayout");

let make = (~diets, ~restrictions, ~currentMenu, _children) => {
  ...component,
  initialState: () => { selectedDietId: Belt.List.head(diets) },
  reducer: (_action, state) =>
    switch (_action) {
    | Noop => ReasonReact.NoUpdate
    },
  render: self =>
    <div>
      <div className=mainPageContentFedFilterClass>
        <FedFilter diets selectedDietId=self.state.selectedDietId />
      </div>
      <FedMenuSection />
    </div>
};