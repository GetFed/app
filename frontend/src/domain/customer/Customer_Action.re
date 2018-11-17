/* done */
type action =
  | NoOp;

type model = Customer_Model.Record.t;

let rec reduce = (action, promise: Js.Promise.t(model)): Js.Promise.t(model) =>
  promise
  |> Js.Promise.then_((customer: model) => {
       let {local, data}: model = customer;

       switch (action) {
       | NoOp => customer |> Js.Promise.resolve
       };
     });