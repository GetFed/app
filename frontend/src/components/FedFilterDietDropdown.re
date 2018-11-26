
let css = Css.css;
let tw = Css.tw;

let logoClass = [%bs.raw {| css(tw`
`)|}];

type state = {
  dropdownOpen: bool,
};

let defaultState = {
  dropdownOpen: false,
};

type action =
  | OpenDropdown
  | CloseDropdown;

let component = ReasonReact.reducerComponent("FedFilterDietDropdown");

let make = (~diets: list(Diet.Model.idType), ~selectedDiet: Diet.Model.Record.t, _children) => {
  ...component,
  initialState: () => defaultState,
  reducer: (action, state) =>
    switch (action) {
    | OpenDropdown => ReasonReact.Update({...state, dropdownOpen: true})
    | CloseDropdown => ReasonReact.Update({...state, dropdownOpen: false})
    },
  render: self =>
    switch(self.state.dropdownOpen){
    | true =>
        diets
        |> Belt.List.map(_, (dietId) => {
          dietId
          |> Diet.Container.getRecordById
          |> Belt.Option.map(_, (diet) => <DietButton data=diet/>)
        })
        |> Utils.List.removeOptionsFromList(_)
        |> Utils.ReasonReact.listToReactArray
    | false =>
        <DietButton data=selectedDiet/>
    }
};