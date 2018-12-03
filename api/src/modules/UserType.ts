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

      defaultAddress: {
        type: Address.Type,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return user.address_line_1 ? user._id : null;
        },
      },

      amountSpent: {
        type: GraphQLFloat,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "amount_spent");
        },
      },

      restrictions: {
        type: Restriction.Connection.connectionType,
        args: connectionArgs,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return connectionFromArray(_.get(user, "restrictions") || [], args);
        },
      },

      credit: {
        type: GraphQLFloat,
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "credit");
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
        resolve: async (idObj, args, context) => {
          const user = await UserLoader.load(context, idObj);
          return _.get(user, "phone");
        },
      },

      sessions: {
        type: Session.Connection.connectionType,
        args: connectionArgs,
        resolve: async (idObj, args, context) => {
          return null; /* come back in a min */
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
          return _.get(user, "stripe_id");
        },
      },

      publicProfile: {
        type: PublicProfile.Type,
        resolve: async (idObj, args, context) =>  {
          const user = await UserLoader.load(context, idObj);
          return user._id; /* TODO don't expose ids here */
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
