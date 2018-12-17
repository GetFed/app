let component = ReasonReact.statelessComponent("FedTextArea");

let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let fedTextAreaClass = [%bs.raw {| css(tw`
  p-4
  w-full
  text-lg
  rounded-lg
  border-green-darker
`)|}];

let make = (~value, ~onTextChange, ~placeholder, ~type_="string", _children) => {
  ...component,
  render: _self =>
    <TextInput
      value
      onTextChange
      placeholder
      type_
      className=fedTextAreaClass
    />
};