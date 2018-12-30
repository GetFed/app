module Model = Attribute_Model;

module ModelSchema = Schema.Attribute;
module Record = ModelSchema.AddModel(Model);

module Action = Attribute_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);