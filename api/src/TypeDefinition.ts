import Dataloader from 'dataloader';

import { UserModel } from './model/user';

const { IUser } = UserModel;
import {UserLoader} from './model/user';

type Key = string;

export type Dataloaders = {
  UserLoader: Dataloader<Key, IUser>;
};

export type GraphQLContext = {
  user?: UserLoader;
  dataloaders: Dataloaders;
};
