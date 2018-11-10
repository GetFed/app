// @flow

import { GraphQLObjectType } from 'graphql';

import UserMutations from './user';

export default new GraphQLObjectType({
  name: 'Mutation',
  fields: () => ({
    ...UserMutations,
  }),
});
