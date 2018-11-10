// @flow
/* eslint-disable no-multi-assign,prefer-const */

import UserModel from '../src/model/UserModel';

export const restartCounters = () => {
  global.__COUNTERS__ = Object.keys(global.__COUNTERS__).reduce((prev, curr) => ({ ...prev, [curr]: 0 }), {});
};

export const createUser = async (payload: Object = {}) => {
  const n = (global.__COUNTERS__.user += 1);

  return new UserModel({
    name: `Normal user ${n}`,
    email: `user-${n}@example.com`,
    password: '123456',
    active: true,
    ...payload,
  }).save();
};
