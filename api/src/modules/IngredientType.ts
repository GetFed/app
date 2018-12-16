import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLString,
  GraphQLList,
  GraphQLID
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';
import { connectionArgs, connectionFromArray } from 'graphql-relay';
const TYPE_NAME = 'Ingredient';

import * as RestrictionModel from '../model/non_standard/RestrictionModel';

import { Loader as ItemLoader } from '../model/ItemModel';

import * as Restriction from './RestrictionType';
import * as NutritionFacts from './NutritionFactsType';
import * as Attribute from './AttributeType';

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
    description: 'Ingredient type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          if(!item) { return idObj; }
          return item.id;
        },
      },
      name: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          if(!item) { return idObj; }
          return item.name;
        },
      },
      description: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          if(!item) { return ""; }
          return item.description;
        },
      },
      restrictions: {
        type: Restriction.Connection.connectionType,
        args: connectionArgs,
        resolve: async (idObj: string, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          const restrictions = (
            item
            ? Object.entries(item.warnings)
                .filter(([key, value]) => value && warningToRestriction[key])
                .map(([key, value]) => warningToRestriction[key])
            : []);

          return connectionFromArray(restrictions, args);
        },
      },
      nutritionFacts: {
        type: GraphQLNonNull(NutritionFacts.Type),
        resolve: async (idObj: string, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          if(!item) { return idObj; }
          return item._id;
        },
      },
      attributes: {
        type: GraphQLNonNull(Attribute.Connection.connectionType),
        resolve: async (idObj: string, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          const attributes =
            item
            ? Object.entries(item.attributes)
                .filter(([key, value]) => key && value)
                .map(([key, value]) => key)
            : [];
          return connectionFromArray(attributes, args);
        },
      },
      ingredients: {
        type: GraphQLNonNull(Connection.connectionType),
        resolve: async (idObj: string, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          const ingredients = ((item && item.ingredients) || []).filter((i) => i);

          console.log("ingredients = %j", ingredients);

          return connectionFromArray(ingredients, args);
        },
      },
      /* this needs to connectionType an array */
      ingredientIds: {
        type: GraphQLNonNull(GraphQLList(GraphQLString)),
        resolve: async (idObj: string, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          const ingredients = ((item && item.ingredients) || []).filter((i) => i);
          return ingredients;
        },
      },
      photo: {
        type: GraphQLNonNull(GraphQLString),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj);
          if(!item) { return ""; }
          return item.photo;
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);