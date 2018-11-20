type t = [
  | `Teacher(Teacher.Model.Record.t)
  | `Customer(Customer.Model.Record.t)
];

let modelTypeToRecordType =
    (recordType: t): (Schema.schemaType, UUID.t) =>
  switch (recordType) {
  | `Teacher(teacher) => (`TeacherSchema, teacher.data.id)
  | `Customer(customer) => (`CustomerSchema, customer.data.id)
  };