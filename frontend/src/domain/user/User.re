module Model = User_Model;
module Action = User_Action;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, User_Model);
module Mutation = User_Mutation;