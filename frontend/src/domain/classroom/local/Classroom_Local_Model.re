type classroomTab = string;
type testTab = string;

type _record = {
  newTestId: Schema.testId(Schema.modelIdType),
  newStudentId: Schema.studentId(Schema.modelIdType),
  tab: classroomTab,
  testTab,
  selectedStudent: option(Schema.studentId(Schema.modelIdType)),
};

let _defaultRecord = id => {
  module UUIDSeedType = {
    let namespace = id;
  };
  module Rand = UUID.V5Random(UUIDSeedType);

  {
    newTestId: `TestId(Rand.generateSeqUUID()),
    newStudentId: `StudentId(Rand.generateSeqUUID()),
    tab: "roster",
    testTab: "",
    selectedStudent: None,
  };
};

module Record = {
  type t = _record;
  let default = _defaultRecord;
};