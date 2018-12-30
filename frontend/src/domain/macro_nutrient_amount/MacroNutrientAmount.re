module Model = MacroNutrientAmount_Model;

module ModelSchema = Schema.MacroNutrientAmount;
module Record = ModelSchema.AddModel(Model);

module Action = MacroNutrientAmount_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);