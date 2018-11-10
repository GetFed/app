import Dataloader from 'dataloader';

import { UserModel } from './model/user';

const { IUser } = UserModel;
import {Loader as UserLoader} from './model/user/UserModel';


type Key = string;

export type Dataloaders = {
  UserLoader: Dataloader<Key, IUser>;
};

export type GraphQLContext = {
  user?: UserLoader;
  dataloaders: Dataloaders;
};
