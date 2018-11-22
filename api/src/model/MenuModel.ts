import mongoose, { Document, Model } from 'mongoose';
import {createLoader} from '../loader/LoaderCreator';

import {IModel as IDeliveryWindowModel} from './DeliveryWindowModel';
import {IModel as IItemModel} from './ItemModel';

// can only access data if defined on schema
const schema = new mongoose.Schema(
  {
    _id: String,
    name: String,
    createdAt: Date,
    online_at: Date,
    custom_until: Date,
    offline_at: Date,
    ready_by: Date,
    id_number: Number,
    items: [String],
    delivery_windows: [String] 
  },
  {
    timestamps: {
      createdAt: 'createdAt',
      updatedAt: 'updatedAt',
    },
    collection: 'Menus',
  }
);

export interface IModel extends Document {
  _id: string,
  name: string,
  createdAt: Date;
  online_at: Date;
  custom_until: Date;
  offline_at: Date;
  ready_by: Date;
  id_number: number;
  items: string[];
  delivery_windows: string[];
};

// this will make find, findOne typesafe
const DataModel: Model<IModel> = mongoose.model('Menus', schema);
export const Loader = createLoader(DataModel);

export default DataModel;
