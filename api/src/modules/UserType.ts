import {
  GraphQLObjectType,
  GraphQLString,
  GraphQLList,
  GraphQLBoolean,
  GraphQLNonNull,
  GraphQLFloat,
  GraphQLID
} from 'graphql';
// import { globalIdField } from 'graphql-relay';

import {
  GraphQLDateTime
} from 'graphql-iso-date';

import { connectionDefinitions } from '../core/connection/CustomConnectionType';
import { registerType, nodeInterface } from '../interface/NodeInterface';
import { UserLoader } from '../loader';
import EmailType from './EmailType';

const UserType = registerType(
  new GraphQLObjectType({
    name: 'User',
    description: 'User data',
    fields: () => ({
      // id: globalIdField('User'),
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (id, args, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain._id: null
        },
      },

      createdAt: {
        type: GraphQLString,
        resolve: async (id, args, context) => null,
      },

      emails: {
        type: GraphQLList(EmailType),
        resolve: async (id, args, context) => [],
      },

      stripeId: {
        type: GraphQLString,
        resolve: async (id, args, context) => null,
      },

      firstName: {
        type: GraphQLString,
        resolve: async (id, args, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain.name: null
        },
      },
      lastName: {
        type: GraphQLString,
        resolve: async (id, args, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain.name: null
        },
      },
      
      amountSpent: {
        type: GraphQLFloat,
        resolve: async (id, args, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain.email: null
        },
      },

      lastPurchaseDate: {
        type: GraphQLDateTime,
        resolve: async (id, args, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain.email: null
        },
      },

      discount: {
        type: GraphQLFloat,
        resolve: async (id, args, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain.email: null
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);

export default UserType;

export const UserConnection = connectionDefinitions({
  name: 'User',
  nodeType: GraphQLNonNull(UserType),
});
