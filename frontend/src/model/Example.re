let classroomId = "3af01091-89a2-4df5-87be-61a7009ea0fd";

let testFn = () => {
  let testClassroom =
    `Classroom(
      {
        data: {
          id: classroomId,
          name: "name",
          studentIds: [],
          testIds: [],
        },
        local: Classroom_Local.Model.Record.default(classroomId),
      }: Classroom.Model.Record.t,
    );

  let fullSchema = [];

  let fullSchema2 =
    MyNormalizr.normalizerCommitItemToSchema(fullSchema, testClassroom);
  Js.log("fullSchema2 = ");
  Js.log(fullSchema2);

  let testClassroom2 =
    `Classroom(
      {
        data: {
          id: classroomId,
          name: "name2",
          studentIds: [],
          testIds: [],
        },
        local: Classroom_Local.Model.Record.default(classroomId),
      }: Classroom.Model.Record.t,
    );

  let fullSchema3 =
    MyNormalizr.normalizerCommitItemToSchema(fullSchema2, testClassroom2);
  Js.log("fullSchema3 = ");
  Js.log(fullSchema3);

  let testClassroom3 =
    `Classroom(
      {
        data: {
          id: "classroomId nadf",
          name: "name234",
          studentIds: [],
          testIds: [],
        },
        local: Classroom_Local.Model.Record.default(classroomId),
      }: Classroom.Model.Record.t,
    );

  let fullSchema4 =
    MyNormalizr.normalizerCommitItemToSchema(fullSchema3, testClassroom3);
  Js.log("fullSchema4 = ");
  Js.log(fullSchema4);

  let result =
    MyNormalizr.Converter.Classroom.Remote.getRecord(
      fullSchema4,
      `ClassroomId(classroomId),
    );
  Js.log("result = ");
  Js.log(result);

  switch (result) {
  | None => Js.log("NONE")
  | Some(classroom) =>
    Js.log("Classroom Id");
    Js.log("classroom.id");
    Js.log(classroom.data.id);
  };
};