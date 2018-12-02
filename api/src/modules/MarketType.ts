import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';
import { Loader as MenuLoader } from '../model/MenuModel';

import * as MarketItem from './MarketItemType';

import { connectionArgs, connectionFromArray } from 'graphql-relay';

const TYPE_NAME = 'Menu';

// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Menu type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => {
          const menu = await MenuLoader.load(context, idObj);
          return menu._id;
        },
      },
      items: {
        type: GraphQLNonNull(MarketItem.Connection.connectionType),
        args: connectionArgs,
        resolve: async (idObj, args, context) => {
          const menu = await MenuLoader.load(context, idObj);
          console.log("menu.items = %j", menu.items);
          return connectionFromArray(menu.items, args);
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
