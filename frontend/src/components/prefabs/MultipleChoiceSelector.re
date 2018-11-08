let component = ReasonReact.statelessComponent("MultipleChoiceSelector");
let css = Css.css;
let tw = Css.tw;

type selectionType('a) = {
  id: 'a,
  text: string,
};
type selections('a) = list(selectionType('a));

let fullWidthClass = [%bs.raw {| css(tw` w-full`)|}];
let rowClass = [%bs.raw {| css(tw` w-full m-0`)|}];
let radioInputClass = [%bs.raw {| css(tw` mr-4`)|}];
let make =
    (
      ~selectedId: 'a,
      ~selections: selections('a),
      ~onSelect: 'a => 'b,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div className=fullWidthClass>
      {
        selections
        |> Belt.List.map(_, selection =>
             <div key={selection.id} className=rowClass>
               <input
                 _type="radio"
                 className=radioInputClass
                 value="option1"
                 id={selection.text}
                 checked={selection.id == selectedId}
                 onChange={_ => onSelect(selection.id) |> ignore}
               />
               <label htmlFor={selection.text}>
                 {ReasonReact.string(selection.text)}
               </label>
             </div>
           )
        |> Utils.ReasonReact.listToReactArray
      }
    </div>,
};