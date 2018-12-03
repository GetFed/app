// @flow

import { GraphQLObjectType, GraphQLString, GraphQLNonNull, GraphQLID } from 'graphql';
import { connectionArgs, connectionFromArray, fromGlobalId } from 'graphql-relay';

import { Type as UserType, Connection as UserConnection } from '../modules/UserType';
import { Type as DietType, Connection as DietConnection } from '../modules/DietType';
import { Type as MenuItemType } from '../modules/MenuItemType';
import { Type as RestrictionType, Connection as RestrictionConnection } from '../modules/RestrictionType';
import { Type as MenuType } from '../modules/MenuType';
import { Type as CustomerType } from '../modules/CustomerType';
import { nodeField } from '../interface/NodeInterface';
import UserModel, { Loader as UserLoader } from '../model/UserModel';
import MenuModel, { Loader as MenuLoader } from '../model/MenuModel';
import { Loader as ItemLoader } from '../model/ItemModel';

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
    menuItem: {
      type: MenuItemType,
      args: {
        id: {
          type: new GraphQLNonNull(GraphQLID),
        },
      },
      resolve: async (obj, args, context) => {
        let menuItem = await ItemLoader.load(context, args.id);
        return menuItem._id;
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
        const users = await UserModel.find(where, { _id: 1 }).sort({ createdAt: -1 });
        
        return connectionFromArray(users.map((u) => u._id), args);
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
      type: GraphQLNonNull(DietConnection.connectionType),
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
      type: GraphQLNonNull(RestrictionConnection.connectionType),
      resolve: async (obj, args, context) => {
        return connectionFromArray(restrictionAll, args);
      },
    },
  }),
});
