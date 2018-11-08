[@bs.module "react-icons/lib/fa"]
external comp : ReasonReact.reactClass = "FaChevronLeft";

let make = (~style=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "style": Js.Nullable.fromOption(style)
    },
    children
  );