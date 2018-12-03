// external imports
import { GraphQLObjectType } from 'graphql';

import UserSubscriptions from './user';

export default new GraphQLObjectType({
  name: 'ApiSubscription',
  fields: {
    ...UserSubscriptions,
  },
});
