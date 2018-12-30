
module FullReduced =
      ModelUtils.AddRecord(
        ModelUtils.AddRecord(
          ModelUtils.AddRecord(
            ModelUtils.AddRecord(
              ModelUtils.AddRecord(
                ModelUtils.AddRecord(
                  ModelUtils.AddRecord(
                    ModelUtils.AddRecord(
                      ModelUtils.AddRecord(
                        ModelUtils.AddRecord(
                          ModelUtils.AddRecord(
                            ModelUtils.AddRecord(
                              ModelUtils.AddRecord(
                                ModelUtils.AddRecord(
                                  ModelUtils.AddRecord(
                                    ModelUtils.EmptyNormalizr(ModelUtils.RootModel),
                                  Teacher.Record),
                                  Customer.Record), 
                                  Menu.Record), 
                                  MenuItem.Record),
                                  Diet.Record),
                                  Restriction.Record),
                                  NutritionFacts.Record),
                                  MacroNutrientAmount.Record),
                                  MineralNutrientAmount.Record),
                                  Nutrient.Record),
                                  Attribute.Record),
                                  Ingredient.Record),
                                  IngredientBaseSpread.Record),
                                  FoodProduct.Record),
                                  ProductBase.Record);

module Converter = {
  module Teacher = NormalizrSetup.DomainTypeConverter(Teacher, FullReduced, Teacher.Container, Teacher.Record.Wrapper);
  module Customer = NormalizrSetup.DomainTypeConverter(Customer, FullReduced, Customer.Container, Customer.Record.Wrapper);
  module Menu = NormalizrSetup.DomainTypeConverter(Menu, FullReduced, Menu.Container, Menu.Record.Wrapper);
  module MenuItem = NormalizrSetup.DomainTypeConverter(MenuItem, FullReduced, MenuItem.Container, MenuItem.Record.Wrapper);
  module Diet = NormalizrSetup.DomainTypeConverter(Diet, FullReduced, Diet.Container, Diet.Record.Wrapper);
  module Restriction = NormalizrSetup.DomainTypeConverter(Restriction, FullReduced, Restriction.Container, Restriction.Record.Wrapper);
  module NutritionFacts = NormalizrSetup.DomainTypeConverter(NutritionFacts, FullReduced, NutritionFacts.Container, NutritionFacts.Record.Wrapper);
  module MacroNutrientAmount = NormalizrSetup.DomainTypeConverter(MacroNutrientAmount, FullReduced, MacroNutrientAmount.Container, MacroNutrientAmount.Record.Wrapper);
  module MineralNutrientAmount = NormalizrSetup.DomainTypeConverter(MineralNutrientAmount, FullReduced, MineralNutrientAmount.Container, MineralNutrientAmount.Record.Wrapper);
  module Nutrient = NormalizrSetup.DomainTypeConverter(Nutrient, FullReduced, Nutrient.Container, Nutrient.Record.Wrapper);
  module Attribute = NormalizrSetup.DomainTypeConverter(Attribute, FullReduced, Attribute.Container, Attribute.Record.Wrapper);
  module Ingredient = NormalizrSetup.DomainTypeConverter(Ingredient, FullReduced, Ingredient.Container, Ingredient.Record.Wrapper);
  module IngredientBaseSpread = NormalizrSetup.DomainTypeConverter(IngredientBaseSpread, FullReduced, IngredientBaseSpread.Container, IngredientBaseSpread.Record.Wrapper);
  module FoodProduct = NormalizrSetup.DomainTypeConverter(FoodProduct, FullReduced, FoodProduct.Container, FoodProduct.Record.Wrapper);
  module ProductBase = NormalizrSetup.DomainTypeConverter(ProductBase, FullReduced, ProductBase.Container, ProductBase.Record.Wrapper);
};
