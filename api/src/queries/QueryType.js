// @flow

import { GraphQLObjectType, GraphQLString, GraphQLNonNull, GraphQLID } from 'graphql';
import { connectionArgs, fromGlobalId } from 'graphql-relay';

import { Type as UserType, Connection as UserConnection } from '../modules/UserType';
import { Type as CustomerType } from '../modules/CustomerType';
import { nodeField } from '../interface/NodeInterface';
import UserModel, { Loader as UserLoader } from '../model/UserModel';

type UserArgs = ConnectionArguments & {
  search?: string;
};

export default new GraphQLObjectType({
  name: 'Query',
  description: 'The root of all... queries',
  fields: () => ({
    node: nodeField,
    me: {
      type: CustomerType,
      args: {
        userId: {
          type: GraphQLID,
        },
        id: {
          type: new GraphQLNonNull(GraphQLID),
        },
        sessionId: {
          type: new GraphQLNonNull(GraphQLID),
        },
      },
      resolve: async (root, args, context) => {
        return {
          id: args.id,
          userId: context.user ? context.user._id : null,
          sessionId: args.sessionId
        };
      },
    },
    user: {
      type: UserType,
      args: {
        id: {
          type: new GraphQLNonNull(GraphQLID),
        },
      },
      resolve: async (obj, args, context) => {
        const { id } = fromGlobalId(args.id);
        return UserLoader.load(context, id);
      },
    },
    users: {
      type: UserConnection.connectionType,
      args: {
        ...connectionArgs,
        search: {
          type: GraphQLString,
        },
      },
      resolve: async (obj, args, context) => {
        const where = args.search ? { name: { $regex: new RegExp(`^${args.search}`, 'ig') } } : {};
        const users = UserModel.find(where, { _id: 1 }).sort({ createdAt: -1 });

        return UserLoader.loadMany(users, args, context);
      },
    },
  }),
});
