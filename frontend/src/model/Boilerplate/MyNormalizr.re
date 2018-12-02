module Converter = {
  module Teacher = NormalizrSetup.DomainTypeConverter(Teacher, Teacher.Container, NormalizrRecordType.Wrapper.Teacher);
  module Customer = NormalizrSetup.DomainTypeConverter(Customer, Customer.Container, NormalizrRecordType.Wrapper.Customer);
  module Menu = NormalizrSetup.DomainTypeConverter(Menu, Menu.Container, NormalizrRecordType.Wrapper.Menu);
  module MenuItem = NormalizrSetup.DomainTypeConverter(MenuItem, MenuItem.Container, NormalizrRecordType.Wrapper.MenuItem);
  module Diet = NormalizrSetup.DomainTypeConverter(Diet, Diet.Container, NormalizrRecordType.Wrapper.Diet);
  module Restriction = NormalizrSetup.DomainTypeConverter(Restriction, Restriction.Container, NormalizrRecordType.Wrapper.Restriction);
  module NutritionFacts = NormalizrSetup.DomainTypeConverter(NutritionFacts, NutritionFacts.Container, NormalizrRecordType.Wrapper.NutritionFacts);
  module MacroNutrientAmount = NormalizrSetup.DomainTypeConverter(MacroNutrientAmount, MacroNutrientAmount.Container, NormalizrRecordType.Wrapper.MacroNutrientAmount);
  module MineralNutrientAmount = NormalizrSetup.DomainTypeConverter(MineralNutrientAmount, MineralNutrientAmount.Container, NormalizrRecordType.Wrapper.MineralNutrientAmount);
  module Nutrient = NormalizrSetup.DomainTypeConverter(Nutrient, Nutrient.Container, NormalizrRecordType.Wrapper.Nutrient);
  module Attribute = NormalizrSetup.DomainTypeConverter(Attribute, Attribute.Container, NormalizrRecordType.Wrapper.Attribute);
  module Ingredient = NormalizrSetup.DomainTypeConverter(Ingredient, Ingredient.Container, NormalizrRecordType.Wrapper.Ingredient);
  module FoodProduct = NormalizrSetup.DomainTypeConverter(FoodProduct, FoodProduct.Container, NormalizrRecordType.Wrapper.FoodProduct);
  module Food = NormalizrSetup.DomainTypeConverter(Food, Food.Container, NormalizrRecordType.Wrapper.Food);
  module ProductBase = NormalizrSetup.DomainTypeConverter(ProductBase, ProductBase.Container, NormalizrRecordType.Wrapper.ProductBase);
};