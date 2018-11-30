module Teacher = {
  let schema = `TeacherSchema;
  type idType = [`TeacherId(UUID.t)];
  type idAsType('a) = [> | `TeacherId(UUID.t)] as 'a;
  type schemaType = [`TeacherSchema];
};

module User = {
  let schema = `UserSchema;
  type idType = [`UserId(UUID.t)];
  type idAsType('a) = [> | `UserId(UUID.t)] as 'a;
  type schemaType = [`UserSchema];
};

module Customer = {
  let schema = `CustomerSchema;
  type idType = [`CustomerId(UUID.t)];
  type idAsType('a) = [> | `CustomerId(UUID.t)] as 'a;
  type schemaType = [`CustomerSchema];
};

module Menu = {
  let schema = `MenuSchema;
  type idType = [`MenuId(UUID.t)];
  type idAsType('a) = [> | `MenuId(UUID.t)] as 'a;
  type schemaType = [`MenuSchema];
};

module MenuItem = {
  let schema = `MenuItemSchema;
  type idType = [`MenuItemId(UUID.t)];
  type idAsType('a) = [> | `MenuItemId(UUID.t)] as 'a;
  type schemaType = [`MenuItemSchema];
};

module Diet = {
  let schema = `DietSchema;
  type idType = [`DietId(UUID.t)];
  type idAsType('a) = [> | `DietId(UUID.t)] as 'a;
  type schemaType = [`DietSchema];
};

module Restriction = {
  let schema = `RestrictionSchema;
  type idType = [`RestrictionId(UUID.t)];
  type idAsType('a) = [> | `RestrictionId(UUID.t)] as 'a;
  type schemaType = [`RestrictionSchema];
};

module NutritionFacts = {
  let schema = `NutritionFactsSchema;
  type idType = [`NutritionFactsId(UUID.t)];
  type idAsType('a) = [> | `NutritionFactsId(UUID.t)] as 'a;
  type schemaType = [`NutritionFactsSchema];
};

module MacroNutrientAmount = {
  let schema = `MacroNutrientAmountSchema;
  type idType = [`MacroNutrientAmountId(UUID.t)];
  type idAsType('a) = [> | `MacroNutrientAmountId(UUID.t)] as 'a;
  type schemaType = [`MacroNutrientAmountSchema];
};

module MineralNutrientAmount = {
  let schema = `MineralNutrientAmountSchema;
  type idType = [`MineralNutrientAmountId(UUID.t)];
  type idAsType('a) = [> | `MineralNutrientAmountId(UUID.t)] as 'a;
  type schemaType = [`MineralNutrientAmountSchema];
};

module Nutrient = {
  let schema = `NutrientSchema;
  type idType = [`NutrientId(UUID.t)];
  type idAsType('a) = [> | `NutrientId(UUID.t)] as 'a;
  type schemaType = [`NutrientSchema];
};

module Attribute = {
  let schema = `AttributeSchema;
  type idType = [`AttributeId(UUID.t)];
  type idAsType('a) = [> | `AttributeId(UUID.t)] as 'a;
  type schemaType = [`AttributeSchema];
};

module Ingredient = {
  let schema = `IngredientSchema;
  type idType = [`IngredientId(UUID.t)];
  type idAsType('a) = [> | `IngredientId(UUID.t)] as 'a;
  type schemaType = [`IngredientSchema];
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
/* 

module type SchemaType = {
  type idType = [`None];
  type idAsType('a);
  type schema = [`None];
};

module type FullSchema = {
  type id;
  type schema;
};

module EmptySchema = {
  type id;
  type schema;
};

module ProcessSchema = (
  PrevFullSchema : FullSchema,
  Schema : SchemaType
) : (
      FullSchema
        with type id = [PrevFullSchema.id | Schema.idType]
        and type schema = [PrevFullSchema.schema | Schema.schema]
    ) => {
  type id = [PrevFullSchema.id | Schema.idType];
  type schema = [PrevFullSchema.schema | Schema.schema];
};

module NewSchema = ProcessSchema(EmptySchema, Ingredient);
module NewSchema2 = ProcessSchema(NewSchema, Ingredient); */

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