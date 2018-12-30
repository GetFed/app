[@bs.module "react-icons/fa"]
external comp : ReasonReact.reactClass = "FaBars";

let make = (~className=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "className": Js.Nullable.fromOption(className)
    },
    children
  );