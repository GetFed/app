
let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

type id = string;

let dropdownSelectorClass = [%bs.raw {| css(tw`
  relative
  w-full
`)|}];

let dropdownSelectorSelectorClass = [%bs.raw {| css(tw`
  h-full
  flex
  flex-col
`)|}];

let dropdownSelectorOptionClass = [%bs.raw {| css(tw`
  absolute
  pin-t
  h-full
`)|}];

let dropdownSelectorHiddenClass = [%bs.raw {| css(tw`
  relative
  hidden
`)|}];

let dropdownSelectorClickableClass = [%bs.raw {| css(tw`
  w-full
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

let selectorComponent = (selected, send, toSelectorButton) =>
  <div onClick=((_) => send(CloseDropdown))>
    {selected |> toSelectorButton}
  </div>

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
    <div className=dropdownSelectorClass>
      {
        switch(self.state.dropdownOpen){
        | true =>
            <div className=dropdownSelectorSelectorClass>
              {selectorComponent(selected, self.send, toSelectorButton)}
              <div className=dropdownSelectorOptionClass>
                {
                  (
                    [
                      selectorComponent(selected, self.send, toSelectorButton)
                    ] @
                    (
                      selection
                      |> Belt.List.map(_, (buttonOption: id) =>
                        <div className=dropdownSelectorClickableClass onClick=((_) => self.send(CloseDropdownWithAfterEffect(buttonOption)))>
                          {buttonOption |> toOptionButton}
                        </div>
                      )
                    )
                  )
                  |> Utils.ReasonReact.listToReactArray
                }
              </div>
            </div>
        | false =>
            <div className=dropdownSelectorSelectorClass onClick=((_) => self.send(OpenDropdown))>
              {selectorComponent(selected, self.send, toSelectorButton)}
            </div>
        }
      }
    </div>
};