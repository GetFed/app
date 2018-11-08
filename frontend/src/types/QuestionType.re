type t = [ | `MULTIPLE_CHOICE | `LONG_ANSWER];

let all = () => [`MULTIPLE_CHOICE, `LONG_ANSWER];

let questionTypeToString = (questionType: t): string =>
  switch (questionType) {
  | `MULTIPLE_CHOICE => "Multiple Choice"
  | `LONG_ANSWER => "Long Response"
  };