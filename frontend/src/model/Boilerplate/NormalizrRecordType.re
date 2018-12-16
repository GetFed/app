module Wrapper = {
  module Teacher = {
    type model = Teacher.Model.Record.t;
    type record = [`Teacher(model)];
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
    type record = [`Customer(model)];
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
    type record = [`Menu(model)];
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
    type record = [`MenuItem(model)];
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
    type record = [`Diet(model)];
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
    type record = [`Restriction(model)];
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
    type record = [`NutritionFacts(model)];
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
    type record = [`MacroNutrientAmount(model)];
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
    type record = [`MineralNutrientAmount(model)];
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
    type record = [`Nutrient(model)];

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
    type record = [`Attribute(model)];
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
    type record = [`Ingredient(model)];
    let wrap = model => `Ingredient(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `Ingredient(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module FoodProduct = {
    type model = FoodProduct.Model.Record.t;
    type record = [`FoodProduct(model)];
    let wrap = model => `FoodProduct(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `FoodProduct(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module IngredientBaseSpread = {
    type model = IngredientBaseSpread.Model.Record.t;
    type record = [`IngredientBaseSpread(model)];
    let wrap = model => `IngredientBaseSpread(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `IngredientBaseSpread(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  };

  module ProductBase = {
    type model = ProductBase.Model.Record.t;
    type record = [`ProductBase(model)];
    let wrap = model => `ProductBase(model);
    let unwrap = recordType =>
      switch (recordType) {
      | `ProductBase(model) => Some(model)
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
  | Wrapper.IngredientBaseSpread.record
  | Wrapper.FoodProduct.record
  | Wrapper.ProductBase.record
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
  | `IngredientBaseSpread(data) => (Schema.IngredientBaseSpread.schema, data.data.id)
  | `FoodProduct(data) => (Schema.FoodProduct.schema, data.data.id)
  | `ProductBase(data) => (Schema.ProductBase.schema, data.data.id)
  };
