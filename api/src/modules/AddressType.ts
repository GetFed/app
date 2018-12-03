import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLString,
  GraphQLID,
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';

import { Loader as UserLoader } from '../model/UserModel';

import * as PostalCode from './PostalCodeType';

const TYPE_NAME = 'Address';

// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Address type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => idObj,
      },
      userId: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return user._id;
        },
      },
      firstName: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          console.log("user = %j", user);
          console.log("user.first_name = %j", user.first_name);
          return user.first_name;
        },
      },
      lastName: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return user.last_name;
        },
      },
      addressLine1: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return user.address_line_1;
        },
      },
      addressLine2: {
        type: GraphQLString,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return user.address_line_2;
        },
      },
      addressCity: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return user.address_city;
        },
      },
      addressState: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return user.address_state;
        },
      },
      addressZip: {
        type: GraphQLNonNull(PostalCode.Type),
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return user.address_zipcode;
        },
      },
      deliveryComments: {
        type: GraphQLString,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return user.deliv_comments;
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
