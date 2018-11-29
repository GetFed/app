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


/* Can be put into normizr */

module Converter = {
  module Teacher = NormalizrSetup.DomainTypeConverter(Teacher, Teacher.Container, Wrapper.Teacher);
  module Customer = NormalizrSetup.DomainTypeConverter(Customer, Customer.Container, Wrapper.Customer);
  module Menu = NormalizrSetup.DomainTypeConverter(Menu, Menu.Container, Wrapper.Menu);
  module MenuItem = NormalizrSetup.DomainTypeConverter(MenuItem, MenuItem.Container, Wrapper.MenuItem);
  module Diet = NormalizrSetup.DomainTypeConverter(Diet, Diet.Container, Wrapper.Diet);
  module Restriction = NormalizrSetup.DomainTypeConverter(Restriction, Restriction.Container, Wrapper.Restriction);
  module NutritionFacts = NormalizrSetup.DomainTypeConverter(NutritionFacts, NutritionFacts.Container, Wrapper.NutritionFacts);
  module MacroNutrientAmount = NormalizrSetup.DomainTypeConverter(MacroNutrientAmount, MacroNutrientAmount.Container, Wrapper.MacroNutrientAmount);
  module MineralNutrientAmount = NormalizrSetup.DomainTypeConverter(MineralNutrientAmount, MineralNutrientAmount.Container, Wrapper.MineralNutrientAmount);
  module Nutrient = NormalizrSetup.DomainTypeConverter(Nutrient, Nutrient.Container, Wrapper.Nutrient);
  module Attribute = NormalizrSetup.DomainTypeConverter(Attribute, Attribute.Container, Wrapper.Attribute);
  module Ingredient = NormalizrSetup.DomainTypeConverter(Ingredient, Ingredient.Container, Wrapper.Ingredient);
};

/* module TeacherMutation = MutationNormalizr.GetRecord(Teacher.Container); */
