
let css = Css.css;
let tw = Css.tw;

type id = string;

let dropdownSelectorClass = [%bs.raw {| css(tw`
  flex
  flex-col
`)|}];

type state = {
  dropdownOpen: bool,
};

let defaultState = {
  dropdownOpen: false,
};

type action =
  | OpenDropdown
  | CloseDropdown
  | CloseDropdownWithAfterEffect(id);

let component = ReasonReact.reducerComponent("DropdownSelector");

let make = (
  ~selection: list(id),
  ~selected: option(id),
  ~toSelectorButton: (option(id)) => ReasonReact.reactElement,
  ~toOptionButton:  (id) => ReasonReact.reactElement,
  ~afterSelect: ((id) => unit),
  _children
) => {
  ...component,
  initialState: () => defaultState,
  reducer: (action, _state) =>
    switch (action) {
    | OpenDropdown => ReasonReact.Update({dropdownOpen: true})
    | CloseDropdown => ReasonReact.Update({dropdownOpen: false})
    | CloseDropdownWithAfterEffect(selectedOption: id) =>
        ReasonReact.UpdateWithSideEffects(
          {dropdownOpen: false},
          (_) => selectedOption |> afterSelect |> ignore
        )
    },
  render: self =>
    switch(self.state.dropdownOpen){
    | true =>
        <div className=dropdownSelectorClass>
          {
            <div onClick=((_) => self.send(CloseDropdown))>
              {selected |> toSelectorButton}
            </div>
          }
          {
            selection
            |> Belt.List.map(_, (buttonOption: id) =>
                <div onClick=((_) => self.send(CloseDropdownWithAfterEffect(buttonOption)))>
                  {buttonOption |> toOptionButton}
                </div>
              )
            |> Utils.ReasonReact.listToReactArray
          }
        </div>
    | false =>
        <div className=dropdownSelectorClass onClick=((_) => self.send(OpenDropdown))>
          {toSelectorButton(selected)}
        </div>
    }
};