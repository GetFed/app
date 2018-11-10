import { Loader as UserLoader } from '../model/UserModel';
// const files = require.context('../model');
// console.log("files = %j", files);

const loaders = [
  UserLoader
];

export const dataloaders = loaders.reduce(
  (prev, loader) => ({
    ...prev,
    [loader.loaderName]: loader.getLoader(),
  }),
  {},
);
