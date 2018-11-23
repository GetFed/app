/* done */
type action =
  | NoOp;

type model = Menu_Model.Record.t;

let rec reduce = (action, promise: Js.Promise.t(model)): Js.Promise.t(model) =>
  promise
  |> Js.Promise.then_((menu: model) => {
       let {local, data}: model = menu;
       switch (action) {
       | NoOp => menu |> Js.Promise.resolve
       };
     });