module Model = Nutrient_Model;

module ModelSchema = Schema.Nutrient;
module Record = ModelSchema.AddModel(Model);

module Action = Nutrient_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);