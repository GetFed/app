// @flow

import { GraphQLObjectType, GraphQLString, GraphQLNonNull, GraphQLID } from 'graphql';
import { connectionArgs, connectionFromArray, fromGlobalId } from 'graphql-relay';

import { Type as UserType, Connection as UserConnection } from '../modules/UserType';
import { Type as DietType, Connection as DietConnection } from '../modules/DietType';
import { Type as RestrictionType, Connection as RestrictionConnection } from '../modules/RestrictionType';
import { Type as MenuType } from '../modules/MenuType';
import { Type as CustomerType } from '../modules/CustomerType';
import { nodeField } from '../interface/NodeInterface';
import UserModel, { Loader as UserLoader } from '../model/UserModel';
import MenuModel, { Loader as MenuLoader } from '../model/MenuModel';

import { all as dietAll } from '../model/non_standard/DietModel';
import { all as restrictionAll } from '../model/non_standard/RestrictionModel';

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
    currentMenu: {
      type: MenuType,
      resolve: async (obj, args, context) => {
        const user = await MenuModel.findOne({active: true}, { _id: 1 }).sort({ createdAt: -1 });
        return user._id;
      },
    },
    diets: {
      type: DietConnection.connectionType,
      args: {
        ...connectionArgs,
        search: {
          type: GraphQLString,
        },
      },
      resolve: async (obj, args, context) => {
        return connectionFromArray(dietAll, args);
      },
    },
    restrictions: {
      type: RestrictionConnection.connectionType,
      resolve: async (obj, args, context) => {
        return connectionFromArray(restrictionAll, args);
      },
    },
  }),
});
