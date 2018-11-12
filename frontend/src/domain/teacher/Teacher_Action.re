/* done */
type action =
  | ApolloAddClassroom(ApolloType.t)
  | NoOp;

type model = Teacher_Model.Record.t;

let rec reduce = (action, promise: Js.Promise.t(model)): Js.Promise.t(model) =>
  promise
  |> Js.Promise.then_((teacher: model) => {
       let {local, data}: model = teacher;

       switch (action) {
       /* both below */
       | ApolloAddClassroom(apollo) =>
         apollo
         |> ApolloType.runApollo
         |> Utils.Promise.runBothIgnoreFirst(
              _,
              Js.Promise.resolve(
                {
                  local: local,
                  data: teacher.data,
                }: model,
              ),
            )
       | NoOp => teacher |> Js.Promise.resolve
       };
     });