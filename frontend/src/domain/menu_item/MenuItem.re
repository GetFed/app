module Model = MenuItem_Model;

module ModelSchema = Schema.MenuItem;
module Record = ModelSchema.AddModel(Model);

module Action = MenuItem_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);