module Model = Menu_Model;

module ModelSchema = Schema.Menu;
module Record = ModelSchema.AddModel(Model);

module Action = Menu_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);