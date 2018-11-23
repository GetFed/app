import mongoose, { Document, Model } from 'mongoose';
import {createLoader} from '../loader/LoaderCreator';

// can only access data if defined on schema
const schema = new mongoose.Schema(
  {
    _id: String,
    name: String,
    category: String,
    description: String
  },
  {
    collection: 'Items',
  }
);

export interface IModel extends Document {
  _id: string,
  name: string,
  category: string,
  description: string,
};

// this will make find, findOne typesafe
const DataModel: Model<IModel> = mongoose.model('Items', schema);
export const Loader = createLoader(DataModel);

export default DataModel;
