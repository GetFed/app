type teacherModal =
  | Classroom
  | Test;

type _record = {
  newTestId: Schema.testId(Schema.modelIdType),
  newClassroomId: Schema.classroomId(Schema.modelIdType),
  addingNewClassroom: bool,
  sidebarSelection: SideTab.t,
  subSidebarSelection: string,
  selectedClassroomId: option(Schema.classroomId(Schema.modelIdType)),
  openDropdown: list((SideTab.t, bool)),
  openModal: option(teacherModal),
};

let _defaultRecord = id => {
  module UUIDSeedType = {
    let namespace = id;
  };
  module Rand = UUID.V5Random(UUIDSeedType);
  {
    newTestId: `TestId(Rand.generateSeqUUID()),
    newClassroomId: `ClassroomId(Rand.generateSeqUUID()),
    addingNewClassroom: false,
    sidebarSelection: SideTab.Dashboard,
    subSidebarSelection: "",
    selectedClassroomId: None,
    openDropdown: [(SideTab.Classroom, true), (SideTab.Test, true)],
    openModal: None,
  };
};

module Record = {
  type t = _record;
  let default = _defaultRecord;
};