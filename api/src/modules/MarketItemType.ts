import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';

const TYPE_NAME = 'MarketItem';

// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Market Item type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => idObj,
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
