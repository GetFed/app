module Model = ProductBase_Model;

module ModelSchema = Schema.ProductBase;
module Record = ModelSchema.AddModel(Model);

module Action = ProductBase_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);