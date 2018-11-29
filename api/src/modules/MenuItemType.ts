import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLString,
  GraphQLID,
  GraphQLFloat,
} from 'graphql';

import { connectionArgs, connectionFromArray } from 'graphql-relay';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';
import { Loader as ItemLoader } from '../model/ItemModel';

import * as Restriction from './RestrictionType';
import * as NutritionFacts from './NutritionFactsType';
import * as RestrictionModel from '../model/non_standard/RestrictionModel';

const TYPE_NAME = 'MenuItem';

const warningToRestriction = {
  "peanuts" : RestrictionModel.TypeId.PEANUTS,
  "treenuts" : RestrictionModel.TypeId.NUTS,
  "soy" : RestrictionModel.TypeId.SOY,
  "beef" : RestrictionModel.TypeId.BEEF,
  "chicken" : RestrictionModel.TypeId.CHICKEN,
  "fish" : RestrictionModel.TypeId.FISH,
  "shellfish" : RestrictionModel.TypeId.SHELLFISH,
  "milk" : RestrictionModel.TypeId.DAIRY,
  "eggs" : RestrictionModel.TypeId.EGGS,
  "wheat" : RestrictionModel.TypeId.GLUTEN
};

// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Menu Item type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item._id;
        },
      },
      name: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item.name;
        },
      },
      description: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item.description;
        },
      },
      photo: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item.photo;
        },
      },
      price: {
        type: GraphQLNonNull(GraphQLFloat),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item.price_per_unit;
        },
      },
      restrictions: {
        type: Restriction.Connection.connectionType,
        args: connectionArgs,
        resolve: async (idObj: string, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          const restrictions = 
            Object.entries(item.warnings)
              .filter(([key, value]) => value && warningToRestriction[key])
              .map(([key, value]) => warningToRestriction[key]);

          return connectionFromArray(restrictions, args);
        },
      },
      nutritionFacts: {
        type: GraphQLNonNull(NutritionFacts.Type),
        resolve: async (idObj: string, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item._id;
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
