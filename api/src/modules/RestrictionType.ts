import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLID,
  GraphQLString
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';

const TYPE_NAME = 'Restriction';

import * as Restriction from '../model/non_standard/RestrictionModel';

const stringToTypeId = (idString: string): Restriction.TypeId | null => {
  if(idString === "beef") { return Restriction.TypeId.BEEF; }
  if(idString === "chicken") { return Restriction.TypeId.CHICKEN; }
  if(idString === "fish") { return Restriction.TypeId.FISH; }
  if(idString === "shellfish") { return Restriction.TypeId.SHELLFISH; }
  if(idString === "dairy") { return Restriction.TypeId.DAIRY; }
  if(idString === "eggs") { return Restriction.TypeId.EGGS; }
  if(idString === "gluten") { return Restriction.TypeId.GLUTEN; }
  if(idString === "peanuts") { return Restriction.TypeId.PEANUTS; }
  if(idString === "nuts") { return Restriction.TypeId.NUTS; }
  if(idString === "soy") { return Restriction.TypeId.SOY; }
  return null;
};

// idObj is id: String
export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Restriction type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => idObj,
      },
      name: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => idObj,
      },
      image: {
        type: GraphQLString,
        resolve: async (idObj, args, context) => {
          const typeId = stringToTypeId(idObj);
          if(!typeId) { return null; }
          return Restriction.DATABASE_OBJECT[typeId].image
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
