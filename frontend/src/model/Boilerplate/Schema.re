module Teacher = {
  type idType = [`TeacherId(UUID.t)];
  type idAsType('a) = [> | `TeacherId(UUID.t)] as 'a;
  type schema = [`TeacherSchema];
};

module User = {
  type idType = [`UserId(UUID.t)];
  type idAsType('a) = [> | `UserId(UUID.t)] as 'a;
  type schema = [`UserSchema];
};

module Customer = {
  type idType = [`CustomerId(UUID.t)];
  type idAsType('a) = [> | `CustomerId(UUID.t)] as 'a;
  type schema = [`CustomerSchema];
};

module Menu = {
  type idType = [`MenuId(UUID.t)];
  type idAsType('a) = [> | `MenuId(UUID.t)] as 'a;
  type schema = [`MenuSchema];
};

module MenuItem = {
  type idType = [`MenuItemId(UUID.t)];
  type idAsType('a) = [> | `MenuItemId(UUID.t)] as 'a;
  type schema = [`MenuItemSchema];
};

module Diet = {
  type idType = [`DietId(UUID.t)];
  type idAsType('a) = [> | `DietId(UUID.t)] as 'a;
  type schema = [`DietSchema];
};

module Restriction = {
  type idType = [`RestrictionId(UUID.t)];
  type idAsType('a) = [> | `RestrictionId(UUID.t)] as 'a;
  type schema = [`RestrictionSchema];
};

module NutritionFacts = {
  type idType = [`NutritionFactsId(UUID.t)];
  type idAsType('a) = [> | `NutritionFactsId(UUID.t)] as 'a;
  type schema = [`NutritionFactsSchema];
};

module MacroNutrientAmount = {
  type idType = [`MacroNutrientAmountId(UUID.t)];
  type idAsType('a) = [> | `MacroNutrientAmountId(UUID.t)] as 'a;
  type schema = [`MacroNutrientAmountSchema];
};

module MineralNutrientAmount = {
  type idType = [`MineralNutrientAmountId(UUID.t)];
  type idAsType('a) = [> | `MineralNutrientAmountId(UUID.t)] as 'a;
  type schema = [`MineralNutrientAmountSchema];
};

module Nutrient = {
  type idType = [`NutrientId(UUID.t)];
  type idAsType('a) = [> | `NutrientId(UUID.t)] as 'a;
  type schema = [`NutrientSchema];
};

module Attribute = {
  type idType = [`AttributeId(UUID.t)];
  type idAsType('a) = [> | `AttributeId(UUID.t)] as 'a;
  type schema = [`AttributeSchema];
};

module Ingredient = {
  type idType = [`IngredientId(UUID.t)];
  type idAsType('a) = [> | `IngredientId(UUID.t)] as 'a;
  type schema = [`IngredientSchema];
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
];

/* pass as type id to domains */

/* Id only file above */

/* can belong to domain */
type schemaType = [
  | Teacher.schema
  | Customer.schema
  | User.schema
  | Menu.schema
  | MenuItem.schema
  | Diet.schema
  | Restriction.schema
  | NutritionFacts.schema
  | MacroNutrientAmount.schema
  | MineralNutrientAmount.schema
  | Nutrient.schema
  | Attribute.schema
  | Ingredient.schema
];

/* Generate by Normalizr */
let modelIdToIdFunction = (recordIdType: modelIdType): (schemaType, UUID.t) =>
  switch (recordIdType) {
  | `TeacherId(uuid) => (`TeacherSchema, uuid)
  | `CustomerId(uuid) => (`CustomerSchema, uuid)
  | `UserId(uuid) => (`UserSchema, uuid)
  | `MenuId(uuid) => (`MenuSchema, uuid)
  | `MenuItemId(uuid) => (`MenuItemSchema, uuid)
  | `DietId(uuid) => (`DietSchema, uuid)
  | `RestrictionId(uuid) => (`RestrictionSchema, uuid)
  | `NutritionFactsId(uuid) => (`NutritionFactsSchema, uuid)
  | `MacroNutrientAmountId(uuid) => (`MacroNutrientAmountSchema, uuid)
  | `MineralNutrientAmountId(uuid) => (`MineralNutrientAmountSchema, uuid)
  | `NutrientId(uuid) => (`NutrientSchema, uuid)
  | `AttributeId(uuid) => (`AttributeSchema, uuid)
  | `IngredientId(uuid) => (`IngredientSchema, uuid)
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