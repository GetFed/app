module Model = Restriction_Model;

module ModelSchema = Schema.Restriction;
module Record = ModelSchema.AddModel(Model);

module Action = Restriction_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);