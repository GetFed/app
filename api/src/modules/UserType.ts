import {
  GraphQLObjectType,
  GraphQLString,
  GraphQLNonNull,
  GraphQLFloat,
  GraphQLID
} from 'graphql';

import { connectionArgs, connectionFromArray } from 'graphql-relay';

import { GraphQLDateTime } from 'graphql-iso-date';
import _ from 'lodash';

import Hashids from 'hashids';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';
import { Loader as UserLoader } from '../model/UserModel';

import * as Email from './EmailType';
import * as Address from './AddressType';
import * as Restriction from './RestrictionType';
import * as Promo from './PromoType';
import * as PublicProfile from './PublicProfileType';
import * as RoleGroup from './RoleGroupType';
import * as Session from './SessionType';



const hashids = new Hashids();


const TYPE_NAME = 'User';

// idObj is String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'User data',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => {
          const userAgain = await UserLoader.load(context, idObj);
          return userAgain ? userAgain._id: null
        },
      },

      createdAt: {
        type: GraphQLDateTime,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "createdAt")
        },
      },

      addresses: {
        type: Address.Connection.connectionType,
        args: connectionArgs,
        resolve: async (idObj, args, context) => {
          return null;
        },
      },

      amountSpent: {
        type: GraphQLFloat,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "email");
        },
      },

      lastPurchaseDate: {
        type: GraphQLDateTime,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "lastPurchaseDate");
        },
      },

      restrictions: {
        type: Restriction.Connection.connectionType,
        args: connectionArgs,
        resolve: async (idObj, args, context) => {
          return null;
        },
      },

      credit: {
        type: GraphQLFloat,
        resolve: async (idObj, args, context) => {
          return 0.0;
        },
      },

      emails: {
        type: Email.Connection.connectionType,
        args: connectionArgs,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          const address = _.get(user, "emails", []).map(({address}) => ({address, id: idObj}));
          return connectionFromArray(address, args);
        },
      },

      phoneNumber: {
        type: GraphQLString,
        args: connectionArgs,
        resolve: async (idObj, args, context) => {
          return "";
        },
      },

      sessions: {
        type: Session.Connection.connectionType,
        args: connectionArgs,
        resolve: async (idObj, args, context) => {
          return null;
        },
      },

      discount: {
        type: GraphQLFloat,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "discount");
        },
      },

      referral: {
        type: Promo.Type,
        resolve: async (idObj, args, context) => {
          return null;
        },
      },

      stripeId: {
        type: GraphQLString,
        resolve: async (idObj, args, context) =>  {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "stripeId");
        },
      },

      publicProfile: {
        type: PublicProfile.Type,
        resolve: async (idObj, args, context) =>  {
          return null;
        },
      },

      roleGroup: {
        type: RoleGroup.Type,
        resolve: async (idObj, args, context) =>  {
          return null;
        },
      },

    }),
    interfaces: () => [nodeInterface],
  }),
);
