import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLID,
  GraphQLFloat,
  GraphQLString
} from 'graphql';

import { Loader as ItemLoader } from '../model/ItemModel';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';

import { camelToCapitalized } from '../utils/string';


const TYPE_NAME = 'MacroNutrientAmount';
import * as Nutrient from './NutrientType';

// idObj is {id: String, name: String}

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'MacroNutrientAmount type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => `${idObj.id} ${idObj.name}`,
      },
      name: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => camelToCapitalized(idObj.name),
      },
      nutrient: {
        type: GraphQLNonNull(Nutrient.Type),
        resolve: async (idObj, args, context) => idObj.name,
      },
      amount: {
        type: GraphQLNonNull(GraphQLFloat),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj.id);
          if(!item) { return 0; }
          return item.nutrition_facts[idObj.name] || 0;
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
