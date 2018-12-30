module Model = Customer_Model;

module ModelSchema = Schema.Customer;
module Record = ModelSchema.AddModel(Model);

module Action = Customer_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);