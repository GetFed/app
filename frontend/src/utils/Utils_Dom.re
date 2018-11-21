let getValueDoAction = (runOnVal, event) =>
  event
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
  |> (domObj => domObj##value |> runOnVal)
  |> ignore;

let combineStyles = (outsideStyleMaybe, textAreaStyle) =>
  switch (outsideStyleMaybe) {
  | None => textAreaStyle
  | Some(style) => ReactDOMRe.Style.combine(textAreaStyle, style)
  };

/* copied from  ReasonReact */
let parseUrl = url =>
  switch (url) {
  | ""
  | "/" => []
  | _ =>
    /* remove the preceeding /, which every pathname seems to have */
    let raw = Js.String.sliceToEnd(~from=1, url);
    /* remove the trailing /, which some pathnames might have. Ugh */
    let raw =
      switch (Js.String.get(raw, Js.String.length(raw) - 1)) {
      | "/" => Js.String.slice(~from=0, ~to_=-1, raw)
      | _ => raw
      };
    raw |> Js.String.split("/") |> Array.to_list;
  };