/* done */
type action =
  | NoOp;

type model = Ingredient_Model.Record.t;

let rec reduce = (action, promise: Js.Promise.t(model)): Js.Promise.t(model) =>
  promise
  |> Js.Promise.then_((model) => {
       let {local, data}: model = model;
       switch (action) {
       | NoOp => model |> Js.Promise.resolve
       };
     });