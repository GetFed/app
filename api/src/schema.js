// @flow

import { GraphQLSchema } from 'graphql';

import QueryType from './queries/QueryType';
import MutationType from './mutations/MutationType';
import SubscriptionType from './subscriptions/SubscriptionType';

export const schema = new GraphQLSchema({
  query: QueryType,
  mutation: MutationType,
  subscription: SubscriptionType,
});
