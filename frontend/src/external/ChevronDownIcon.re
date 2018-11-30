[@bs.module "react-icons/lib/fa/chevron-down"]
external comp : ReasonReact.reactClass = "default";

let make = (~style=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "style": Js.Nullable.fromOption(style)
    },
    children
  );