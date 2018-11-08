let component = ReasonReact.statelessComponent("MultipleChoiceLayout");

let make = (~multipleChoiceId, ~normalized, ~onSelect, ~selectedId, _children) => {
  ...component,
  render: _self => {
    let multipleChoice =
      normalized
      |> MyNormalizr.Converter.MultipleChoice.Remote.getRecord(
           _,
           multipleChoiceId,
         )
      |> Belt.Option.getWithDefault(
           _,
           MultipleChoice.Model.Record.defaultWithId((), multipleChoiceId),
         );

    <MultipleChoiceSelector
      key={multipleChoice.data.id}
      selectedId
      selections={
        Belt.List.map(multipleChoice.data.choices, choice =>
          (
            {id: choice.text, text: choice.text}:
              MultipleChoiceSelector.selectionType(string)
          )
        )
      }
      onSelect
    />;
  },
};