import { MODELS } from '../model';

const LOADERS = MODELS.map(({Loader}) => Loader);

export const dataloaders = LOADERS.reduce(
  (prev, loader) => ({
    ...prev,
    [loader.loaderName]: loader.getLoader(),
  }),
  {},
);
