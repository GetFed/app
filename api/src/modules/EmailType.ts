import {
  GraphQLObjectType,
  GraphQLString,
  GraphQLBoolean,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';
import { Loader as UserLoader } from '../model/UserModel';

import _ from 'lodash';

const TYPE_NAME = 'Email';

// idObj is {id: String, email: String}

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Email type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => `${idObj.id} ${idObj.address}`,
      },

      address: {
        type: GraphQLString,
        resolve: async (idObj, args, context) => idObj.address,
      },

      verified: {
        type: GraphQLBoolean,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj.id);
          const addressObj = _.get(user, "emails", []).find(({address}) => address === idObj.address);
          return _.get(addressObj, "verified", false);
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
