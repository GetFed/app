// @flow

import jwt from 'jsonwebtoken';
import UserModel from './model/UserModel';
import SessionModel from './model/SessionModel';
import { jwtSecret } from './config';

const splitOutJwt = (token) => {
  return token.split(" ")[1];
};

const getUserIdFromToken = async (token) => {
  const session = await SessionModel.findOne({ token });
  return await UserModel.findOne({ _id: session.userId });
};

export async function getUser(token: string) {
  if (!token) return { user: null };

  try {
    const parsedToken = splitOutJwt(token);
    const decodedToken = jwt.verify(parsedToken, jwtSecret);
    const user = await getUserIdFromToken(decodedToken.data.token);
    return { user };
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
