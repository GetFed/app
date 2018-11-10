import {
  GraphQLObjectType,
  GraphQLString,
  GraphQLList,
  GraphQLBoolean,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';

import { connectionDefinitions } from '../core/connection/CustomConnectionType';
import { registerType, nodeInterface } from '../interface/NodeInterface';
import { UserLoader } from '../loader';
import EmailType from './EmailType';

export default registerType(
  new GraphQLObjectType({
    name: 'Email',
    description: 'Email type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (id, args, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain._id: null
        },
      },

      email: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (id, args, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain._id: null
        },
      },

      verified: {
        type: GraphQLBoolean,
        resolve: async (id, args, context) => {
          return null
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);