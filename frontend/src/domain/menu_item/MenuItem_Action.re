/* done */
type action =
  | NoOp;

type model = MenuItem_Model.Record.t;

let rec reduce = (action, promise: Js.Promise.t(model)): Js.Promise.t(model) =>
  promise
  |> Js.Promise.then_((menuItem: model) => {
       let {local, data}: model = menuItem;
       switch (action) {
       | NoOp => menuItem |> Js.Promise.resolve
       };
     });