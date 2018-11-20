type state = {normalized: NormalizrSetup.normalizedType};

type action =
  | UpdateNormalizr(NormalizrSetup.normalizedType);

let component = ReasonReact.reducerComponent("NormalizrInit");

let make = (~records: list(NormalizrRecordType.t)=[], children) => {
  ...component,
  initialState: () => {
    normalized:
      Belt.List.reduce(
        records,
        NormalizrNew.Normalizr.defaultNormalized,
        NormalizrSetup.normalizerCommitItemToSchema,
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
        UpdateNormalizr(n)
        |> send(_)
        |> Js.Promise.resolve
      )
    ),
};