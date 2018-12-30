
let css = Css.css;
let tw = Css.tw;

let component = ReasonReact.statelessComponent("FedFilterDietDropdown");

let make = (
  ~diets: list(Diet.Model.idType),
  ~size=FedButton.MEDIUM,
  ~color=FedButton.GREEN,
  ~selectedDietId: Diet.Model.idType,
  ~updateDiet: ((Diet.Model.idType) => unit),
  _children
) => {
  ...component,
  render: self =>
    <DropdownSelector
      selection={diets |> Belt.List.map(_, Diet.Model.getUUIDFromId)}
      selected={Some(Diet.Model.getUUIDFromId(selectedDietId))}
      toSelectorButton={
        (id) =>
          switch(id){
          | Some(selectedId) =>
              selectedId
              |> Diet.Model.idToTypedId
              |> Diet.Container.getRecordById
              |> Belt.Option.mapWithDefault(_, <div/>, (diet) => <DietButton size color data=diet />)
          | None => <div />
          }
      }
      toOptionButton={(selectedId) =>
        selectedId
        |> Diet.Model.idToTypedId
        |> Diet.Container.getRecordById
        |> Belt.Option.mapWithDefault(_, <div/>, (diet) => <DietButton size color data=diet />)
      }
      afterSelect=((id) => id |> Diet.Model.idToTypedId |> updateDiet)
    />
};