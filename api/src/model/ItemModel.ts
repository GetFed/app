import mongoose, { Document, Model } from 'mongoose';
import {createLoader} from '../loader/LoaderCreator';

// can only access data if defined on schema
const schema = new mongoose.Schema(
  {
    _id: String,
    name: String,
    category: String,
    description: String,
    photo: String,
    price_per_unit: Number,
    warnings: {
      peanuts: Boolean,
      treenuts: Boolean,
      soy: Boolean,
      beef: Boolean,
      chicken: Boolean,
      fish: Boolean,
      shellfish: Boolean,
      milk: Boolean,
      eggs: Boolean,
      wheat: Boolean,
    }
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
  photo: string,
  price_per_unit: number,
  warnings: {
    peanuts: boolean,
    treenuts: boolean,
    soy: boolean,
    beef: boolean,
    chicken: boolean,
    fish: boolean,
    shellfish: boolean,
    milk: boolean,
    eggs: boolean,
    wheat: boolean,
  }
};

// this will make find, findOne typesafe
const DataModel: Model<IModel> = mongoose.model('Items', schema);
export const Loader = createLoader(DataModel);

export default DataModel;
