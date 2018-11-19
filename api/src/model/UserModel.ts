import mongoose, { Document, Model } from 'mongoose';
import {createLoader} from '../loader/LoaderCreator';

// can only access data if defined on schema
const schema = new mongoose.Schema({
  _id: String,
  address_zipcode: String,
  emails: {
    type: [
      'Mixed'
    ]
  },
  first_name: String,
  last_name: String,
  phone: String,
  address_city: String,
  address_line_1: String,
  address_line_2: String,
  address_state: String,
  amount_spent: Number,
  createdAt: {
    type: Date
  },
  credit: Number,
  diet: String,
  email: String,
  preferredDelivDay: String,
  profile: {
    zipCode: String
  },
  restrictions: [String],
  stripe_id: String,
  // subscriptions: {
  //   type: [
  //     'Mixed'
  //   ]
  // }
});

export interface IUser extends Document {
  _id: string;
  address_zipcode: string;
  emails: object[];
  first_name: string;
  last_name: string;
  phone: string;
  address_city: string;
  address_line_1: string;
  address_line_2: string;
  address_state: string;
  amount_spent: number;
  createdAt: Date;
  credit: number;
  diet: string;
  email: string;
  preferredDelivDay: string;
  profile: {
    zipCode: string,
  };
  restrictions: string[];
  stripe_id: string;
  subscriptions: object;
  authenticate: (plainTextPassword: string) => boolean;
  encryptPassword: (password: string | undefined) => string;
}

// this will make find, findOne typesafe
const DataModel: Model<IUser> = mongoose.model('User', schema);
export const Loader = createLoader(DataModel);

export default DataModel;
