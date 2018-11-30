type t = [
  | `Teacher(Teacher.Model.Record.t)
  | `Customer(Customer.Model.Record.t)
  | `Menu(Menu.Model.Record.t)
  | `MenuItem(MenuItem.Model.Record.t)
  | `Diet(Diet.Model.Record.t)
  | `Restriction(Restriction.Model.Record.t)
  | `NutritionFacts(NutritionFacts.Model.Record.t)
  | `MacroNutrientAmount(MacroNutrientAmount.Model.Record.t)
  | `MineralNutrientAmount(MineralNutrientAmount.Model.Record.t)
  | `Nutrient(Nutrient.Model.Record.t)
  | `Attribute(Attribute.Model.Record.t)
  | `Ingredient(Ingredient.Model.Record.t)
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
  | `MacroNutrientAmount(data) => (`MacroNutrientAmountSchema, data.data.id)
  | `MineralNutrientAmount(data) => (`MineralNutrientAmountSchema, data.data.id)
  | `Nutrient(data) => (`NutrientSchema, data.data.id)
  | `Attribute(data) => (`AttributeSchema, data.data.id)
  | `Ingredient(data) => (`IngredientSchema, data.data.id)
  };

module Wrapper = {
  module Teacher = {
    type model = Teacher.Model.Record.t;
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
    let wrap = model => `Ingredient(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Ingredient(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };
};
