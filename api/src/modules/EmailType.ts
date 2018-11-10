import {
  GraphQLObjectType,
  GraphQLString,
  GraphQLBoolean,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';

import { connectionDefinitions } from '../core/connection/CustomConnectionType';
import { registerType, nodeInterface } from '../interface/NodeInterface';
import { UserLoader } from '../loader';

const TYPE_NAME = 'Email';

const EmailType = registerType(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Email type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => {
          return `${idObj.id} ${idObj.email}`;
        },
      },

      address: {
        type: GraphQLString,
        resolve: async (idObj, args, context) => {
          return idObj.email
        },
      },

      verified: {
        type: GraphQLBoolean,
        resolve: async (idObj, args, context) => {
          const userAgain = await UserLoader.load(context, idObj.id);
          const addressObj = userAgain && userAgain.emails.find(({address}) => address === idObj.address)
          return addressObj ? addressObj.verified : false;
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);

export default EmailType;

export const EmailConnection = connectionDefinitions({
  name: TYPE_NAME,
  nodeType: GraphQLNonNull(EmailType),
});
