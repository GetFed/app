let component = ReasonReact.statelessComponent("TestRow");

let testRowStyle =
  ReactDOMRe.Style.make(~width="100%", ~border="solid 1px grey", ());

let testRowContent = ReactDOMRe.Style.make(~margin="1em", ~color="grey", ());

let make = (~test: Test.Model.Record.t, ~onClick, ~normalized, _children) => {
  ...component,
  render: _self =>
    <div style=testRowStyle>
      <div style=testRowContent onClick={_ => onClick() |> ignore}>
        <h3> {ReasonReact.string(test.data.name)} </h3>
        <p>
          {
            (test.data.questionIds |> Belt.List.length |> string_of_int)
            ++ " questions"
            ++ (
              Belt.List.length(test.data.objectiveIds) !== 0 ?
                " | categories: "
                ++ (
                  test.data.objectiveIds
                  |> Utils.List.removeOptionsFromList
                  |> MyNormalizr.idListToFilteredItems(
                       _,
                       MyNormalizr.Converter.Objective.Remote.getRecord(
                         normalized,
                       ),
                     )
                  |> Belt.List.map(_, obj => obj.data.text)
                  |> Utils.List.joinStringList(_, ", ")
                ) :
                ""
            )
            |> ReasonReact.string
          }
        </p>
      </div>
    </div>,
};