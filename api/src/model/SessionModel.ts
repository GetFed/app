import mongoose, { Document, Model } from 'mongoose';
import {createLoader} from '../loader/LoaderCreator';

// can only access data if defined on schema
const schema = new mongoose.Schema({
  _id: String,
  userId: String,
  token: String,
  userAgent: String,
  ip: String,
  valid: Boolean,
  createdAt: Date,
  updatedAt: Date,
});

export interface ISession extends Document {
  _id: string,
  userId: string,
  token: string,
  userAgent: string,
  ip: string,
  valid: boolean,
  createdAt: Date,
  updatedAt: Date,
};

// this will make find, findOne typesafe
const DataModel: Model<ISession> = mongoose.model('Session', schema);
export const Loader = createLoader(DataModel);

export default DataModel;
