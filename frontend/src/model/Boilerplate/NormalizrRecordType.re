type t = [
  | `Teacher(Teacher.Model.Record.t)
  | `Customer(Customer.Model.Record.t)
  | `Menu(Menu.Model.Record.t)
  | `MenuItem(MenuItem.Model.Record.t)
  | `Diet(Diet.Model.Record.t)
  | `Restriction(Restriction.Model.Record.t)
  | `NutritionFacts(NutritionFacts.Model.Record.t)
];

let modelTypeToRecordType =
    (recordType: t): (Schema.schemaType, UUID.t) =>
  switch (recordType) {
  | `Teacher(data) => (`TeacherSchema, data.data.id)
  | `Customer(data) => (`CustomerSchema, data.data.id)
  | `Menu(data) => (`MenuSchema, data.data.id)
  | `MenuItem(data) => (`MenuItemSchema, data.data.id)
  | `Diet(data) => (`DietSchema, data.data.id)
  | `Restriction(data) => (`RestrictionSchema, data.data.id)
  | `NutritionFacts(data) => (`NutritionFactsSchema, data.data.id)
  };