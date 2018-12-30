module Model = Ingredient_Model;

module ModelSchema = Schema.Ingredient;
module Record = ModelSchema.AddModel(Model);

module Action = Ingredient_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);