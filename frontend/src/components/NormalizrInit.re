type state = {normalized: MyNormalizr.normalizedType};

type action =
  | UpdateNormalizr(MyNormalizr.normalizedType);

let component = ReasonReact.reducerComponent("NormalizrInit");

let make = (~records: list(MyNormalizr.recordType)=[], children) => {
  ...component,
  initialState: () => {
    normalized:
      Belt.List.reduce(
        records,
        NormalizrNew.Normalizr.defaultNormalized,
        MyNormalizr.normalizerCommitItemToSchema,
      ),
  },
  reducer: (action, _state) =>
    switch (action) {
    | UpdateNormalizr(normalized) =>
      ReasonReact.Update({normalized: normalized})
    },
  render: ({state, send}) =>
    children(~normalized=state.normalized, ~updateNormalizr=norm =>
      norm
      |> Js.Promise.then_(n =>
           UpdateNormalizr(n) |> send(_) |> Js.Promise.resolve
         )
    ),
};