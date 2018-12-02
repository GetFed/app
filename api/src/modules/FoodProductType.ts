import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';

import * as ProductBase from './ProductBaseType';
import * as Food from './FoodType';

const TYPE_NAME = 'FoodProduct';

// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Food Product type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => idObj,
      },
      product: {
        type: GraphQLNonNull(ProductBase.Type),
        resolve: async (idObj, args, context) => idObj,
      },
      food: {
        type: GraphQLNonNull(Food.Type),
        resolve: async (idObj, args, context) => idObj,
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);