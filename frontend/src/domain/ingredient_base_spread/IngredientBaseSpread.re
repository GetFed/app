module Model = IngredientBaseSpread_Model;

module ModelSchema = Schema.IngredientBaseSpread;
module Record = ModelSchema.AddModel(Model);

module Action = IngredientBaseSpread_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);