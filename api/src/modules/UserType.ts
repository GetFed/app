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
import _ from 'lodash';

import { fullConnectionDefinitions } from '../core/connection/CustomConnectionType';
import { registerType, nodeInterface } from '../interface/NodeInterface';
import { Loader as UserLoader } from '../model/user/UserModel';

import {EmailConnection} from './EmailType';

import { connectionArgs } from 'graphql-relay';

const TYPE_NAME = 'User';

// idObj is String

const UserType = registerType(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'User data',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => {
          const userAgain = await UserLoader.load(context, idObj);
          return userAgain ? userAgain._id: null
        },
      },

      createdAt: {
        type: GraphQLDateTime,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "createdAt")
        },
      },

      emails: {
        type: EmailConnection.connectionType,
        args: connectionArgs,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          const address = _.get(user, "emails", []).map(({address}) => ({address, id: idObj}));
          return connectionFromArray(address, args);
        },
      },

      stripeId: {
        type: GraphQLString,
        resolve: async (idObj, args, context) =>  {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "stripeId");
        },
      },

      firstName: {
        type: GraphQLString,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "first_name");
        },
      },
      lastName: {
        type: GraphQLString,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "lastName");
        },
      },
      
      amountSpent: {
        type: GraphQLFloat,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "email");
        },
      },

      lastPurchaseDate: {
        type: GraphQLDateTime,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "lastPurchaseDate");
        },
      },

      discount: {
        type: GraphQLFloat,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "discount");
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);

export default UserType;

// this is how arrays are handled
export const UserConnection = fullConnectionDefinitions(UserType);
