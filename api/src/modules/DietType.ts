import {
  GraphQLObjectType,
  GraphQLString,
  GraphQLBoolean,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';

import { connectionArgs, connectionFromArray } from 'graphql-relay';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';

import * as Restriction from './RestrictionType';

import _ from 'lodash';

const TYPE_NAME = 'Diet';

import * as Diet from '../model/non_standard/DietModel';

const stringToTypeId = (idString: string): Diet.TypeId | null => {
  if(idString === "omnivore") { return Diet.TypeId.OMNIVORE; }
  if(idString === "vegetarian") { return Diet.TypeId.VEGETARIAN; }
  if(idString === "vegan") { return Diet.TypeId.VEGAN; }
  if(idString === "pescatarian") { return Diet.TypeId.PESCATARIAN; }
  if(idString === "paleo") { return Diet.TypeId.PALEO; }
  return null;
};

// idObj is string (name of diet)

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Doet type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => idObj,
      },
      restrictions: {
        type: Restriction.Connection.connectionType,
        args: connectionArgs,
        resolve: async (idObj: string, args, context) => {
          const typeId = stringToTypeId(idObj);
          if (!typeId) { return null; }
          return connectionFromArray(Diet.DATABASE_OBJECT[typeId].restrictions, args);
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
