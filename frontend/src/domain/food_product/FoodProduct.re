module Model = FoodProduct_Model;

module ModelSchema = Schema.FoodProduct;
module Record = ModelSchema.AddModel(Model);

module Action = FoodProduct_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);