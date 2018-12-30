module Model = MineralNutrientAmount_Model;

module ModelSchema = Schema.MineralNutrientAmount;
module Record = ModelSchema.AddModel(Model);

module Action = MineralNutrientAmount_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);