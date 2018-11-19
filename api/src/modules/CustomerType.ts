import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';
import { Type as UserType } from './UserType';
import { Type as SessionType } from './SessionType';

import { Loader as UserLoader } from '../model/UserModel';

const TYPE_NAME = 'Customer';

// idObj is { id: String, user_id: String, session_id: String };

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Customer type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => (`${idObj.id} ${idObj.userId} ${idObj.sessionId}`),
      },
      user: {
        type: UserType,
        resolve: async (idObj, args, context) => {
          return idObj.userId;
        },
      },
      session: {
        type: SessionType,
        resolve: async (idObj, args, context) => {
          return idObj.session_id;
        },
      }
    }),
    interfaces: () => [nodeInterface],
  }),
);