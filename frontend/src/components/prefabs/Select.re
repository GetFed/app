let component = ReasonReact.statelessComponent("Select");

type selectionType('a) = {
  id: 'a,
  text: string,
};
type selections('a) = list(selectionType('a));
type idToString('a) = 'a => string;

let selectStyle =
  ReactDOMRe.Style.make(
    ~padding="0.0em 2.5em 0.0em .5em",
    ~backgroundImage=
      "linear-gradient(45deg, transparent 60%, white 60%), linear-gradient(135deg, white 35%, transparent 35%), linear-gradient(to right, grey, grey), linear-gradient(45deg, transparent 50%, grey 50%), linear-gradient(135deg, grey 50%, transparent 50%), linear-gradient(to right, grey, grey)",
    ~backgroundPosition=
      "calc(100% - 20px) calc(0.6em + 2px), calc(100% - 15px) calc(0.6em + 2px), calc(100% + 1em) 0.0em",
    ~backgroundSize="5px 5px, 5px 5px, 1px 1.0em",
    ~backgroundRepeat="no-repeat",
    ~borderRadius="0",
    (),
  );

let stringToId =
    (selections: selections('a), idToString: idToString('a), s: string)
    : option('a) =>
  selections
  |> Belt.List.getBy(_, (selection: selectionType('a)) =>
       idToString(selection.id) == s
     )
  |> Belt.Option.map(_, s => s.id);

let make =
    (
      ~selectedId: 'a,
      ~selections: selections('a),
      ~idToString,
      ~onSelect: option('a) => 'b,
      _children,
    ) => {
  ...component,
  render: _self => {
    let partialStringToId = stringToId(selections, idToString);
    let valueSelectTest =
      Utils.Dom.getValueDoAction(a => a |> partialStringToId |> onSelect);

    <select
      style=selectStyle
      value={selectedId |> idToString}
      onChange=valueSelectTest>
      {
        selections
        |> Belt.List.map(_, s =>
             <option key={s.id |> idToString} value={s.id |> idToString}>
               {ReasonReact.string(s.text)}
             </option>
           )
        |> Utils.ReasonReact.listToReactArray
      }
    </select>;
  },
};