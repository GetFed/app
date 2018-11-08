[@bs.module "react-icons/lib/ti"]
external comp : ReasonReact.reactClass = "TiTimes";

let make = (~style=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "style": Js.Nullable.fromOption(style)
    },
    children
  );