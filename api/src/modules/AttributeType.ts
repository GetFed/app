import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLString,
  GraphQLID
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';

const TYPE_NAME = 'Attribute';

const camelToCapitalized = (str) => str.split(/(?=[A-Z])/).join(' ').toUpperCase();


// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Attribute type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => idObj,
      },
      name: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => camelToCapitalized(idObj),
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
