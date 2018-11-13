import {
  GraphQLObjectType,
  GraphQLString,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';
import _ from 'lodash';

import { fullConnectionDefinitions } from '../core/connection/CustomConnectionType';
import { registerType, nodeInterface } from '../interface/NodeInterface';
import { Loader as UserLoader } from '../model/UserModel';

const TYPE_NAME = 'PublicProfile';

// idObj is id: String

const SchemaType = registerType(
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

export default SchemaType;

// this is how arrays are handled
export const Connection = fullConnectionDefinitions(SchemaType);
