import DataLoader from 'dataloader';
import { connectionFromMongoCursor, mongooseLoader } from '@entria/graphql-mongoose-loader';
import { Types, Model, Document } from 'mongoose';
import { GraphQLContext } from '../TypeDefinition';

const defaultIdFn = (obj) => obj._id;

export function createLoader<T extends Document>(model: Model<T>) {

  const loaderName = `${model.modelName}Loader`;

  const getLoader = () => new DataLoader(ids => mongooseLoader(model, ids));

  const load = async (context: GraphQLContext, id: string) => {
    if (!id) { return null; }

    let data;
    try {
      data = await context.dataloaders[loaderName].load(id);
    } catch (err) {
      return null;
    }

    return data;
  };

  const clearCache = ({ dataloaders }: GraphQLContext, id: Types.ObjectId) => dataloaders[loaderName].clear(id.toString());
  const primeCache = ({ dataloaders }: GraphQLContext, id: Types.ObjectId, data: T) => dataloaders[loaderName].prime(id.toString(), data);
  const clearAndPrimeCache = (context: GraphQLContext, id: Types.ObjectId, data: T) => clearCache(context, id) && primeCache(context, id, data);

  const loadMany = async (objs, args, context, idFn = defaultIdFn) => {
    
    console.log("objs = %j", objs);
    const mongoObjCursored = await connectionFromMongoCursor({
      cursor: objs,
      context,
      args,
      loader: load,
    });

    const updatedEdges = mongoObjCursored.edges.map(async (edge) => {
      const {node} = edge;
      edge.node = node.then(idFn);
      return edge;
    });

    mongoObjCursored.edges = updatedEdges;
    return mongoObjCursored;
  };

  return {
    loaderName,
    getLoader,
    load,
    clearCache, 
    primeCache,
    clearAndPrimeCache,
    loadMany,
  };
};


