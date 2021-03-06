import { GraphQLObjectType } from 'graphql';
import { offsetToCursor } from 'graphql-relay';

import { Connection as UserConnection } from '../modules/UserType';
import pubSub, { EVENTS } from '../pubSub';

const UserAddedPayloadType = new GraphQLObjectType({
  name: 'UserAddedPayload',
  fields: () => ({
    userEdge: {
      type: UserConnection.edgeType,
      resolve: ({ user }) => ({
        cursor: offsetToCursor(user.id),
        node: user,
      }),
    },
  }),
});

const userAddedSubscription = {
  type: UserAddedPayloadType,
  subscribe: () => pubSub.asyncIterator(EVENTS.USER.ADDED),
};

export default userAddedSubscription;
