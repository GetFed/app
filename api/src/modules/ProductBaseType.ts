import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLFloat,
  GraphQLID
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';

import { Loader as ItemLoader } from '../model/ItemModel';

const TYPE_NAME = 'ProductBase';

// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'ProductBase type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => idObj,
      },
      price: {
        type: GraphQLNonNull(GraphQLFloat),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item.price_per_unit;
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);