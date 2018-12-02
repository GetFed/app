import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLString,
  GraphQLID,
  GraphQLFloat,
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';
import { Loader as ItemLoader } from '../model/ItemModel';

import * as FoodProduct from './FoodProductType';

const TYPE_NAME = 'MenuItem';

// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Menu Item type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item._id;
        },
      },
      name: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item.name;
        },
      },
      description: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item.description;
        },
      },
      photo: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item.photo;
        },
      },
      product: {
        type: GraphQLNonNull(FoodProduct.Type),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item._id;
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
