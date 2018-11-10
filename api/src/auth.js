// @flow

import jwt from 'jsonwebtoken';
import UserModel from './model/UserModel';
import { jwtSecret } from './config';

export async function getUser(token: string) {
  if (!token) return { user: null };

  try {
    const decodedToken = jwt.verify(token.substring(4), jwtSecret);

    const user = await UserModel.findOne({ _id: decodedToken.id });

    return {
      user,
    };
  } catch (err) {
    return { user: null };
  }
}

type UserType = {
  _id: string,
};

export function generateToken(user: UserType) {
  return `JWT ${jwt.sign({ id: user._id }, jwtSecret)}`;
}
