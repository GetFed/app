import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';
import { Type as UserType } from '../modules/UserType';

import { Loader as UserLoader } from '../model/UserModel';

const TYPE_NAME = 'Session';

// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Session type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => "1",
      },
      user: {
        type: UserType,
        resolve: async (root, args, context) => {
          return (context.user ? UserLoader.load(context, context.user._id) : null)
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);