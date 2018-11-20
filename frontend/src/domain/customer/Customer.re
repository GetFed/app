module Model = Customer_Model;
module Action = Customer_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Customer_Model);