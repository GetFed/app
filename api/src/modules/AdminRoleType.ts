import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';

import { fullConnectionDefinitions } from '../core/connection/CustomConnectionType';
import { registerType, nodeInterface } from '../interface/NodeInterface';

const TYPE_NAME = 'AdminRole';

// idObj is id: String

const SchemaType = registerType(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Admin Role type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => "1",
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);

export default SchemaType;

// this is how arrays are handled
export const Connection = fullConnectionDefinitions(SchemaType);
