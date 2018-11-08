[@bs.module "../../../../src/chart.js"]
external col : ReasonReact.reactClass = "default";

/* EXAMPLE OF LOCAL JAVASCRIPT FILE LOADED */
let make = (~data : array('a), ~categorical=?, ~textSize=?, ~width=?, ~binValues=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=col,
    ~props={
      "data": data,
      "color": Colors.secondary,
      "binValues": Js.Nullable.fromOption(binValues),
      "categorical": Js.Nullable.fromOption(categorical),
      "textSize": Js.Nullable.fromOption(textSize),
      "width": Js.Nullable.fromOption(width),
    },
    children
  );