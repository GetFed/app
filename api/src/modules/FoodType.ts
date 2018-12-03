import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLString,
  GraphQLID
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';
import { connectionArgs, connectionFromArray } from 'graphql-relay';
const TYPE_NAME = 'Food';

import * as RestrictionModel from '../model/non_standard/RestrictionModel';

import { Loader as ItemLoader } from '../model/ItemModel';

import * as Restriction from './RestrictionType';
import * as NutritionFacts from './NutritionFactsType';
import * as Attribute from './AttributeType';
import * as Ingredient from './IngredientType';

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
    description: 'Food type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => idObj,
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
      attributes: {
        type: GraphQLNonNull(Attribute.Connection.connectionType),
        resolve: async (idObj: string, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          const attributes = 
            Object.entries(item.attributes)
              .filter(([key, value]) => key && value)
              .map(([key, value]) => key);
          return connectionFromArray(attributes, args);
        },
      },
      ingredients: {
        type: GraphQLNonNull(Ingredient.Connection.connectionType),
        resolve: async (idObj: string, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          const ingredients = (item.ingredients|| []).filter((i) => i)
          return connectionFromArray(ingredients, args);
        },
      },
      photo: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          return item.photo;
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);