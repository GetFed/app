import Dataloader from 'dataloader';

import UserModel from './model/UserModel';


const { IUser } = UserModel;
import {Loader as UserLoader} from './model/UserModel';


type Key = string;

export type Dataloaders = {
  UserLoader: Dataloader<Key, IUser>;
};

export type GraphQLContext = {
  user?: UserLoader;
  dataloaders: Dataloaders;
};
