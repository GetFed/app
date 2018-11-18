let component = ReasonReact.statelessComponent("TextArea");

let make =
    (
      ~style=?,
      ~className=?,
      ~value,
      ~onTextChange,
      ~onKeyDown=?,
      ~placeholder,
      ~onBlur=?,
      ~autoFocus=?,
      _children,
    ) => {
  ...component,
  render: _self =>
    <GenericInput
      isTextArea=true
      ?className
      ?style
      value
      type_="text"
      onTextChange
      ?onKeyDown
      placeholder
      ?onBlur
      ?autoFocus
    />,
};