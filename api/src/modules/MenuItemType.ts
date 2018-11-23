import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLID
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
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => {
          console.log("idObj = %j", idObj);
          const item = await ItemLoader.load(context, idObj);
          console.log("item._id", item.name);
          return item.name
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
