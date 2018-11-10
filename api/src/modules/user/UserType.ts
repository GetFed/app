import { GraphQLObjectType, GraphQLString, GraphQLBoolean, GraphQLNonNull, GraphQLID } from 'graphql';
import { globalIdField } from 'graphql-relay';

import { connectionDefinitions } from '../../core/connection/CustomConnectionType';
import { registerType, nodeInterface } from '../../interface/NodeInterface';
import { UserLoader } from '../../loader';

const UserType = registerType(
  new GraphQLObjectType({
    name: 'User',
    description: 'User data',
    fields: () => ({
      // id: globalIdField('User'),
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (id, abc, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain._id: null
        },
      },
      name: {
        type: GraphQLString,
        resolve: async (id, abc, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain.name: null
        },
      },
      email: {
        type: GraphQLString,
        resolve: async (id, abc, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain.email: null
        },
      },
      active: {
        type: GraphQLBoolean,
        resolve: async (id, abc, context) => {
          const userAgain = await UserLoader.load(context, id);
          return userAgain ? userAgain.active: null
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);

export default UserType;

export const UserConnection = connectionDefinitions({
  name: 'User',
  nodeType: GraphQLNonNull(UserType),
});
