import mongoose, { Document, Model } from 'mongoose';
import {createLoader} from '../loader/LoaderCreator';

// can only access data if defined on schema
const schema = new mongoose.Schema(
  {
    _id: String,
  },
  {
    collection: 'Items',
  }
);

export interface IModel extends Document {
  _id: string,
};

// this will make find, findOne typesafe
const DataModel: Model<IModel> = mongoose.model('Items', schema);
export const Loader = createLoader(DataModel);

export default DataModel;
