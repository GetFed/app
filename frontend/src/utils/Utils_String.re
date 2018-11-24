

let stringToDivHtml = string =>
  string
  |> Js_string.split("\n", _)
  |> Belt.List.fromArray
  |> Belt.List.reduce(
       _,
       [],
       (memo, splitString) => {
         let rand = Random.randomString();
         memo == [] ?
           memo @ [ReasonReact.string(splitString)] :
           memo @ [<br key=rand />] @ [ReasonReact.string(splitString)];
       },
     )
  |> Utils_ReasonReact.listToReactArray;

let toMoney = (number : float) : string =>
  number |> Js.Float.toFixedWithPrecision(_, ~digits=2);