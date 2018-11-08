let objNullableToRecordOptional = (obj, convertToRecord) =>
  switch (Js.Null_undefined.toOption(obj)) {
  | None => None
  | Some(obj) => Some(obj |> convertToRecord)
  };

let recordOptionalToObjNullable = (record, convertToObj) =>
  switch (record) {
  | None => Js.Nullable.null
  | Some(record) => record |> convertToObj |> Js.Nullable.return
  };