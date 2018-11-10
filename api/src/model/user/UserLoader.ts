import DataLoader from 'dataloader';
import { connectionFromMongoCursor, mongooseLoader } from '@entria/graphql-mongoose-loader';
import { Types } from 'mongoose';
import { ConnectionArguments } from 'graphql-relay';

import UserModel, { IUser } from './UserModel';

import { GraphQLContext } from '../../TypeDefinition';

export const getLoader = () => new DataLoader(ids => mongooseLoader(UserModel, ids));

export const load = async (context: GraphQLContext, id: string): Promise<IUser | null> => {
  if (!id) { return null; }

  let data;
  try {
    data = await context.dataloaders.UserLoader.load(id);
  } catch (err) {
    return null;
  }

  return data;
};

export const clearCache = ({ dataloaders }: GraphQLContext, id: Types.ObjectId) => dataloaders.UserLoader.clear(id.toString());
export const primeCache = ({ dataloaders }: GraphQLContext, id: Types.ObjectId, data: IUser) => dataloaders.UserLoader.prime(id.toString(), data);
export const clearAndPrimeCache = (context: GraphQLContext, id: Types.ObjectId, data: IUser) => clearCache(context, id) && primeCache(context, id, data);

type UserArgs = ConnectionArguments & {
  search?: string;
};
export const loadUsers = async (context: GraphQLContext, args: UserArgs) => {
  const where = args.search ? { name: { $regex: new RegExp(`^${args.search}`, 'ig') } } : {};
  const users = UserModel.find(where, { _id: 1 }).sort({ createdAt: -1 });

  const mongoUsersCursored = await connectionFromMongoCursor({
    cursor: users,
    context,
    args,
    loader: load,
  });

  const updatedEdges = mongoUsersCursored.edges.map(async (edge) => {
    const {node} = edge;
    edge.node = node.then(({_id}) => _id);
    return edge;
  });

  mongoUsersCursored.edges = updatedEdges;
  return mongoUsersCursored;
};
