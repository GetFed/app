module Model = Diet_Model;

module ModelSchema = Schema.Diet;
module Record = ModelSchema.AddModel(Model);

module Action = Diet_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);