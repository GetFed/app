import {
  GraphQLObjectType,
  GraphQLString,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';
import _ from 'lodash';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';
import { Loader as UserLoader } from '../model/UserModel';

const TYPE_NAME = 'PublicProfile';

// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Public Profile type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => "1",
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
          return _.get(user, "last_name");
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
