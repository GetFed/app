type t = [
  | `Teacher(Teacher.Model.Record.t)
  | `Customer(Customer.Model.Record.t)
  | `Menu(Menu.Model.Record.t)
  | `MenuItem(MenuItem.Model.Record.t)
];

let modelTypeToRecordType =
    (recordType: t): (Schema.schemaType, UUID.t) =>
  switch (recordType) {
  | `Teacher(teacher) => (`TeacherSchema, teacher.data.id)
  | `Customer(customer) => (`CustomerSchema, customer.data.id)
  | `Menu(menu) => (`MenuSchema, menu.data.id)
  | `MenuItem(menu) => (`MenuItemSchema, menu.data.id)
  };