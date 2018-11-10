import {
  GraphQLObjectType,
  GraphQLString,
  GraphQLList,
  GraphQLBoolean,
  GraphQLNonNull,
  GraphQLFloat,
  GraphQLID
} from 'graphql';
import { connectionFromArray } from 'graphql-relay';

import { GraphQLDateTime } from 'graphql-iso-date';

import { fullConnectionDefinitions } from '../core/connection/CustomConnectionType';
import { registerType, nodeInterface } from '../interface/NodeInterface';
import { UserLoader } from '../loader';
import {EmailConnection} from './EmailType';

const TYPE_NAME = 'User';

const UserType = registerType(
  new GraphQLObjectType({
    name: TYPE_NAME,
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
        type: EmailConnection.connectionType,
        resolve: async (id, args, context) => {
          const user = await UserLoader.load(context, id);
          const address = (user && user.emails && user.emails.map(({address}) => ({address, id}))) || [];
          return connectionFromArray(address, args);
        },
      },

      stripeId: {
        type: GraphQLString,
        resolve: async (id, args, context) => null,
      },

      firstName: {
        type: GraphQLString,
        resolve: async (id, args, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain.first_name: null
        },
      },
      lastName: {
        type: GraphQLString,
        resolve: async (id, args, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain.last_name: null
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

export const UserConnection = fullConnectionDefinitions(UserType);
