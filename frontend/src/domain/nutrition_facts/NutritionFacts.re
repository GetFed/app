module Model = NutritionFacts_Model;

module ModelSchema = Schema.NutritionFacts;
module Record = ModelSchema.AddModel(Model);

module Action = NutritionFacts_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);