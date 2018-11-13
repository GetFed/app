// @flow
import { fromGlobalId, nodeDefinitions } from 'graphql-relay';

import { GraphQLObjectType } from 'graphql';

import * as loaders from '../loader';
import { GraphQLContext } from '../TypeDefinition';
import { fullConnectionDefinitions } from '../core/connection/CustomConnectionType';

type RegisteredTypes = {
  [key: string]: GraphQLObjectType;
};
const registeredTypes: RegisteredTypes = {};

export function registerType(type: GraphQLObjectType) {
  registeredTypes[type.name] = type;
  return type;
}

type Loader = {
  load: (context: GraphQLContext, id: string) => Promise<any>;
};
type Loaders = {
  [key: string]: Loader;
};

export const { nodeField, nodeInterface } = nodeDefinitions(
  (globalId, context: GraphQLContext) => {
    console.log("globalId = %j", globalId);

    const { type, id } = fromGlobalId(globalId);
    // TODO - convert loaders to Loaders

    const loader = loaders[`${type}Loader`];

    return (loader && loader.load(context, id)) || null;
  },
  object => registeredTypes[object.constructor.name] || null,
);

export const fullTypeDefinition = (type: GraphQLObjectType) =>
  ({Type: registerType(type), Connection: fullConnectionDefinitions(type)});
