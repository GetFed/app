type denomType = {
  denom: string,
  nameList: list(string),
  count: int,
};

let denominations = (score, mean, stdDevaition) =>
  switch (score) {
  | score when score < mean -. stdDevaition => "a Low Scores"
  | score when score < mean => "b Mid - Low"
  | score when score < mean +. stdDevaition => "c Mid - High"
  | _ => "d High Scores"
  };

let sum = (sample: list(float)): float =>
  Belt.List.reduce(sample, 0.0, (memo, value) => memo +. value);
let getMean = (sample: list(float)): float =>
  sum(sample) /. (sample |> Belt.List.length |> float_of_int);

let getStdDeviation = (sample: list(float)) => {
  let mean = getMean(sample);
  Belt.List.length(sample) == 1 || Belt.List.length(sample) == 0 ?
    0.0 :
    sample
    |> Belt.List.map(_, value => (value -. mean) *. (value -. mean))
    |> sum
    |> (
      summedValue =>
        sqrt(
          summedValue
          /. (sample |> Belt.List.length |> (n => n - 1 |> float_of_int)),
        )
    );
};

let createScoreDenomHistogram =
    (
      studentScoreList: list((string, float)),
      (mean: float, stdDevaition: float),
    )
    : list(denomType) =>
  studentScoreList
  |> Belt.List.sort(_, ((_, scoreA), (_, scoreB)) =>
       scoreA -. scoreB < 0.0 ? 1 : (-1)
     )
  |> Belt.List.reduce(
       _,
       [],
       (memo, (name, studentScore)) => {
         let denominationStr =
           denominations(studentScore, mean, stdDevaition);
         memo
         |> Belt.List.getBy(_, ((denom, _, _)) => denom == denominationStr)
         |> (
           maybeScoreTuple =>
             switch (maybeScoreTuple) {
             | None => [(denominationStr, [name], 1), ...memo]
             | Some(_) =>
               Belt.List.map(memo, ((denom, nameList, count)) =>
                 denom == denominationStr ?
                   (denom, [name, ...nameList], count + 1) :
                   (denom, nameList, count)
               )
             }
         );
       },
     )
  |> Belt.List.map(_, ((denom, nameList, count)) =>
       {denom, nameList, count}
     );

let calculateZScore =
    (
      studentScoreList: list((string, float)),
      (mean: float, stdDevaition: float),
    )
    : list((string, float)) =>
  Belt.List.map(studentScoreList, ((name, score)) =>
    (name, stdDevaition != 0.0 ? (score -. mean) /. stdDevaition : 0.0)
  );