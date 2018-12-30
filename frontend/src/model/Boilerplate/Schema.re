module ModelGenerator = ModelUtils.GenerateModel(ModelUtils.RootModel);

module Teacher = ModelGenerator();
module User = ModelGenerator();
module Customer = ModelGenerator();
module Menu = ModelGenerator();
module MenuItem = ModelGenerator();
module Diet = ModelGenerator();
module Restriction = ModelGenerator();
module NutritionFacts = ModelGenerator();
module MacroNutrientAmount = ModelGenerator();
module MineralNutrientAmount = ModelGenerator();
module Nutrient = ModelGenerator();
module Attribute = ModelGenerator();
module Ingredient = ModelGenerator();
module IngredientBaseSpread = ModelGenerator();
module FoodProduct = ModelGenerator();
module ProductBase = ModelGenerator();
