import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLID,
  GraphQLInt,
  GraphQLFloat,
  GraphQLString
} from 'graphql';

import { connectionArgs, connectionFromArray } from 'graphql-relay';

import * as MacroNutrientAmount from './MacroNutrientAmountType';
import * as MineralNutrientAmount from './MineralNutrientAmountType';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';
import { Loader as ItemLoader } from '../model/ItemModel';
const TYPE_NAME = 'NutritionFacts';

// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'NutritionFacts type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item._id;
        },
      },
      servingSize: {
        type: GraphQLNonNull(GraphQLFloat),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item.nutrition_facts.servingSize || 0;
        },
      },
      servingsPerContainer: {
        type: GraphQLNonNull(GraphQLFloat),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return "1";
        },
      },
      calories: {
        type: GraphQLNonNull(GraphQLFloat),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          console.log("item = %j", item);
          return item.nutrition_facts.calories || 0;
        },
      },
      caloriesFromFat: {
        type: GraphQLFloat,
        resolve: async (idObj, args, context) => null,
      },
      totalFat: {
        type: GraphQLNonNull(MacroNutrientAmount.Type),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return {id: item._id, name: "totalFat"};
        },
      },
      saturatedFat: {
        type: GraphQLNonNull(MacroNutrientAmount.Type),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return {id: item._id, name: "saturatedFat"};
        },
      },
      transFat: {
        type: MacroNutrientAmount.Type,
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return {id: item._id, name: "transFat"};
        },
      },
      cholesterol: {
        type: GraphQLNonNull(MacroNutrientAmount.Type),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return {id: item._id, name: "cholesterol"};
        },
      },
      sodium: {
        type: GraphQLNonNull(MacroNutrientAmount.Type),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return {id: item._id, name: "sodium"};
        },
      },
      totalCarbohydrate: {
        type: GraphQLNonNull(MacroNutrientAmount.Type),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return {id: item._id, name: "totalCarb"};
        },
      },
      dietaryFiber: {
        type: MacroNutrientAmount.Type,
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return {id: item._id, name: "dietaryFiber"};
        },
      },
      sugar: {
        type: GraphQLNonNull(MacroNutrientAmount.Type),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return {id: item._id, name: "sugars"};
        },
      },
      protein: {
        type: GraphQLNonNull(MacroNutrientAmount.Type),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return {id: item._id, name: "protein"};
        },
      },
      minerals: {
        type: GraphQLNonNull(MineralNutrientAmount.Connection.connectionType),
        args: connectionArgs,
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);

          const pvdNutrition = 
            Object.entries(item.nutrition_facts.PDV)
              .filter(([_, value]) => value)
              .map(([key, _]) => ({id: item._id, name: key}));

          return connectionFromArray(pvdNutrition, args);
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
