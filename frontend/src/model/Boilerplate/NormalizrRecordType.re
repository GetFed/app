module Wrapper = {
  module Teacher = {
    type model = Teacher.Model.Record.t;
    type record = [`Teacher(Teacher.Model.Record.t)];
    let wrap = model => `Teacher(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Teacher(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module Customer = {
    type model = Customer.Model.Record.t;
    type record = [`Customer(Customer.Model.Record.t)];
    let wrap = model => `Customer(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Customer(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module Menu = {
    type model = Menu.Model.Record.t;
    type record = [`Menu(Menu.Model.Record.t)];
    let wrap = model => `Menu(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Menu(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module MenuItem = {
    type model = MenuItem.Model.Record.t;
    type record = [`MenuItem(MenuItem.Model.Record.t)];
    let wrap = model => `MenuItem(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `MenuItem(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module Diet = {
    type model = Diet.Model.Record.t;
    type record = [`Diet(Diet.Model.Record.t)];
    let wrap = model => `Diet(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Diet(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module Restriction = {
    type model = Restriction.Model.Record.t;
    type record = [`Restriction(Restriction.Model.Record.t)];
    let wrap = model => `Restriction(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Restriction(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module NutritionFacts = {
    type model = NutritionFacts.Model.Record.t;
    type record = [`NutritionFacts(NutritionFacts.Model.Record.t)];
    let wrap = model => `NutritionFacts(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `NutritionFacts(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module MacroNutrientAmount = {
    type model = MacroNutrientAmount.Model.Record.t;
    type record = [`MacroNutrientAmount(MacroNutrientAmount.Model.Record.t)];
    let wrap = model => `MacroNutrientAmount(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `MacroNutrientAmount(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module MineralNutrientAmount = {
    type model = MineralNutrientAmount.Model.Record.t;
    type record = [`MineralNutrientAmount(MineralNutrientAmount.Model.Record.t)];
    let wrap = model => `MineralNutrientAmount(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `MineralNutrientAmount(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module Nutrient = {
    type model = Nutrient.Model.Record.t;
    type record = [`Nutrient(Nutrient.Model.Record.t)];

    let wrap = model => `Nutrient(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Nutrient(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module Attribute = {
    type model = Attribute.Model.Record.t;
    type record = [`Attribute(Attribute.Model.Record.t)];
    let wrap = model => `Attribute(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Attribute(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module Ingredient = {
    type model = Ingredient.Model.Record.t;
    type record = [`Ingredient(Ingredient.Model.Record.t)];
    let wrap = model => `Ingredient(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Ingredient(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
};


type t = [
  | Wrapper.Teacher.record
  | Wrapper.Customer.record
  | Wrapper.Menu.record
  | Wrapper.MenuItem.record
  | Wrapper.Diet.record
  | Wrapper.Restriction.record
  | Wrapper.NutritionFacts.record
  | Wrapper.MacroNutrientAmount.record
  | Wrapper.MineralNutrientAmount.record
  | Wrapper.Nutrient.record
  | Wrapper.Attribute.record
  | Wrapper.Ingredient.record
];

let modelTypeToRecordType = (recordType: t): (Schema.schemaType, UUID.t) =>
  switch (recordType) {
  | `Teacher(data) => (Schema.Teacher.schema, data.data.id)
  | `Customer(data) => (Schema.Customer.schema, data.data.id)
  | `Menu(data) => (Schema.Menu.schema, data.data.id)
  | `MenuItem(data) => (Schema.MenuItem.schema, data.data.id)
  | `Diet(data) => (Schema.Diet.schema, data.data.id)
  | `Restriction(data) => (Schema.Restriction.schema, data.data.id)
  | `NutritionFacts(data) => (Schema.NutritionFacts.schema, data.data.id)
  | `MacroNutrientAmount(data) => (Schema.MacroNutrientAmount.schema, data.data.id)
  | `MineralNutrientAmount(data) => (Schema.MineralNutrientAmount.schema, data.data.id)
  | `Nutrient(data) => (Schema.Nutrient.schema, data.data.id)
  | `Attribute(data) => (Schema.Attribute.schema, data.data.id)
  | `Ingredient(data) => (Schema.Ingredient.schema, data.data.id)
  };
