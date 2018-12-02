module Teacher = {
  type schemaType = [`TeacherSchema];
  type idType = [`TeacherId(UUID.t)];
  let schema: [> schemaType] = `TeacherSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module User = {
  type schemaType = [`UserSchema];
  type idType = [`UserId(UUID.t)];
  let schema: [> schemaType] = `UserSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module Customer = {
  type schemaType = [`CustomerSchema];
  type idType = [`CustomerId(UUID.t)];
  let schema: [> schemaType] = `CustomerSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module Menu = {
  type schemaType = [`MenuSchema];
  type idType = [`MenuId(UUID.t)];
  let schema: [> schemaType] = `MenuSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module MenuItem = {
  type schemaType = [`MenuItemSchema];
  type idType = [`MenuItemId(UUID.t)];
  let schema: [> schemaType] = `MenuItemSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module Diet = {
  type schemaType = [`DietSchema];
  type idType = [`DietId(UUID.t)];
  let schema: [> schemaType] = `DietSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module Restriction = {
  type schemaType = [`RestrictionSchema];
  type idType = [`RestrictionId(UUID.t)];
  let schema: [> schemaType] = `RestrictionSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module NutritionFacts = {
  type schemaType = [`NutritionFactsSchema];
  type idType = [`NutritionFactsId(UUID.t)];
  let schema: [> schemaType] = `NutritionFactsSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module MacroNutrientAmount = {
  type schemaType = [`MacroNutrientAmountSchema];
  type idType = [`MacroNutrientAmountId(UUID.t)];
  let schema: [> schemaType] = `MacroNutrientAmountSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module MineralNutrientAmount = {
  type schemaType = [`MineralNutrientAmountSchema];
  type idType = [`MineralNutrientAmountId(UUID.t)];
  let schema: [> schemaType] = `MineralNutrientAmountSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module Nutrient = {
  type schemaType = [`NutrientSchema];
  type idType = [`NutrientId(UUID.t)];
  let schema: [> schemaType] = `NutrientSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module Attribute = {
  type schemaType = [`AttributeSchema];
  type idType = [`AttributeId(UUID.t)];
  let schema: [> schemaType] = `AttributeSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module Ingredient = {
  type schemaType = [`IngredientSchema];
  type idType = [`IngredientId(UUID.t)];
  let schema: [> schemaType] = `IngredientSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module FoodProduct = {
  type schemaType = [`FoodProductSchema];
  type idType = [`FoodProductId(UUID.t)];
  let schema: [> schemaType] = `FoodProductSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module Food = {
  type schemaType = [`FoodSchema];
  type idType = [`FoodId(UUID.t)];
  let schema: [> schemaType] = `FoodSchema;
  type idAsType('a) = [> | idType] as 'a;
};

module ProductBase = {
  type schemaType = [`ProductBaseSchema];
  type idType = [`ProductBaseId(UUID.t)];
  let schema: [> schemaType] = `ProductBaseSchema;
  type idAsType('a) = [> | idType] as 'a;
};

/* need to exist before everything */
type modelIdType = [
  | Teacher.idType
  | User.idType
  | Customer.idType
  | Menu.idType
  | MenuItem.idType
  | Diet.idType
  | Restriction.idType
  | NutritionFacts.idType
  | MacroNutrientAmount.idType
  | MineralNutrientAmount.idType
  | Nutrient.idType
  | Attribute.idType
  | Ingredient.idType
  | FoodProduct.idType
  | Food.idType
  | ProductBase.idType
];

/* pass as type id to domains */

/* Id only file above */

/* can belong to domain */
type schemaType = [
  | Teacher.schemaType
  | Customer.schemaType
  | User.schemaType
  | Menu.schemaType
  | MenuItem.schemaType
  | Diet.schemaType
  | Restriction.schemaType
  | NutritionFacts.schemaType
  | MacroNutrientAmount.schemaType
  | MineralNutrientAmount.schemaType
  | Nutrient.schemaType
  | Attribute.schemaType
  | Ingredient.schemaType
  | FoodProduct.schemaType
  | Food.schemaType
  | ProductBase.schemaType
];

/* Generate by Normalizr */
let modelIdToIdFunction = (recordIdType: modelIdType): (schemaType, UUID.t) =>
  switch (recordIdType) {
  | `TeacherId(uuid) => (Teacher.schema, uuid)
  | `CustomerId(uuid) => (Customer.schema, uuid)
  | `UserId(uuid) => (User.schema, uuid)
  | `MenuId(uuid) => (Menu.schema, uuid)
  | `MenuItemId(uuid) => (MenuItem.schema, uuid)
  | `DietId(uuid) => (Diet.schema, uuid)
  | `RestrictionId(uuid) => (Restriction.schema, uuid)
  | `NutritionFactsId(uuid) => (NutritionFacts.schema, uuid)
  | `MacroNutrientAmountId(uuid) => (MacroNutrientAmount.schema, uuid)
  | `MineralNutrientAmountId(uuid) => (MineralNutrientAmount.schema, uuid)
  | `NutrientId(uuid) => (Nutrient.schema, uuid)
  | `AttributeId(uuid) => (Attribute.schema, uuid)
  | `IngredientId(uuid) => (Ingredient.schema, uuid)
  | `FoodProductId(uuid) => (FoodProduct.schema, uuid)
  | `FoodId(uuid) => (Food.schema, uuid)
  | `ProductBaseId(uuid) => (ProductBase.schema, uuid)
  | `IngredientId(uuid) => (ProductBase.schema, uuid)
  };

/* can come from normalizr module */
let getUUIDFromId = (idType: modelIdType): UUID.t =>
  snd(modelIdToIdFunction(idType));

/* union example */
/* let getQuestionUUIDFromId = (qid: questionId(modelIdType)): UUID.t =>
  switch (qid) {
  | LongAnswer(longAnswerId) => getUUIDFromId(longAnswerId)
  | MultipleChoice(multipleChoiceId) => getUUIDFromId(multipleChoiceId)
  }; */