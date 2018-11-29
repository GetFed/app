import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLString,
  GraphQLID
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';

const TYPE_NAME = 'Nutrient';

const nutrientToUnit = {
  totalFat: "g",
  saturatedFat: "g",
  transFat: "g",
  cholesterol: "mg",
  sodium: "mg",
  totalCarb: "g",
  dietaryFiber: "g",
  sugars: "g",
  protein: "g"
};




// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Nutrient type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => idObj,
      },
      name: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => idObj,
      },
      unit: {
        type: GraphQLString,
        resolve: async (idObj, args, context) => nutrientToUnit[idObj],
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
