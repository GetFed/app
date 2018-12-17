[@bs.module "react-icons/lib/fa/bars"]
external comp : ReasonReact.reactClass = "default";

let make = (~className=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "className": Js.Nullable.fromOption(className)
    },
    children
  );