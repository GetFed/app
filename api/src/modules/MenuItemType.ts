import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLString,
  GraphQLID,
  GraphQLFloat,
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';
import { Loader as ItemLoader } from '../model/ItemModel';

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
          console.log("idObj = %j", idObj);
          const item = await ItemLoader.load(context, idObj);
          console.log("item._id", item._id);
          return item._id
        },
      },
      name: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          console.log("idObj = %j", idObj);
          const item = await ItemLoader.load(context, idObj);
          console.log("item._id", item.name);
          return item.name;
        },
      },
      description: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          console.log("idObj = %j", idObj);
          const item = await ItemLoader.load(context, idObj);
          console.log("item._id", item.description);
          return item.description;
        },
      },
      photo: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          console.log("idObj = %j", idObj);
          const item = await ItemLoader.load(context, idObj);
          console.log("item._id", item.photo);
          return item.photo;
        },
      },
      price: {
        type: GraphQLNonNull(GraphQLFloat),
        resolve: async (idObj, args, context) => {
          console.log("idObj = %j", idObj);
          const item = await ItemLoader.load(context, idObj);
          console.log("item._id", item.price_per_unit);
          return item.price_per_unit;
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
