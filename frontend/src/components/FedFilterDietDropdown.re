
let css = Css.css;
let tw = Css.tw;

let component = ReasonReact.statelessComponent("FedFilterDietDropdown");


let make = (~diets: list(Diet.Model.idType), ~selectedDietId: Diet.Model.idType, _children) => {
  ...component,
  render: self =>
    <DropdownSelector
      selection={diets |> Belt.List.map(_, Schema.getUUIDFromId)}
      selected={Some(Schema.getUUIDFromId(selectedDietId))}
      toSelectorButton={
        (id) =>
          switch(id){
          | Some(selectedId) =>
              `DietId(selectedId)
              |> Diet.Container.getRecordById
              |> Belt.Option.mapWithDefault(_, <div/>, (diet) => <DietButton data=diet />)
          | None => <div />
          }
      }
      toOptionButton={(selectedId) =>
        `DietId(selectedId)
        |> Diet.Container.getRecordById
        |> Belt.Option.mapWithDefault(_, <div/>, (diet) => <DietButton data=diet />)
      }
      afterSelect=((id) => ())
    />
};