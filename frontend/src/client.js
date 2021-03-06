import './client.css';

import React from 'react';
import { hydrate } from 'react-dom';

import App from './init'; // BuckleScript output directory

hydrate(
  <App
    title="Fed | Delicious Dishes Delivered"
    server={false}
  />,
  document.getElementById('root')
);

if (module.hot) {
  module.hot.accept();
}
