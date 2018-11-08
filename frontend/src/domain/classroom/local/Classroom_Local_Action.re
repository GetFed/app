type action =
  | ResetNewStudent
  | ChangeClassroomTab(string)
  | ChangeTestTab(string)
  | SelectStudent(option(Schema.studentId(Schema.modelIdType)));

type model = Classroom_Local_Model.Record.t;

let reduce = (action, local: model) =>
  switch (action) {
  | ResetNewStudent => {
      ...local,
      newStudentId: `StudentId(UUID.generateUUID()),
    }
  | ChangeClassroomTab(tab) => {...local, tab}
  | ChangeTestTab(testTab) => {...local, testTab}
  | SelectStudent(selectedStudent) => {...local, selectedStudent}
  };