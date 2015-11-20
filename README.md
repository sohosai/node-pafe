# node-pafe

Node.js binding to libpafe

:construction: This module provides limited functions only. :construction:

## Features

- Read IDm from FeliCa

## Install

We don't have published this module to npm registry at this time.

```
npm install https://github.com/sohosai/node-pafe.git
```

## Usage

```javascript
var pafe = require('node-pafe');

pafe.readIDm((err, idm) => {
  if (err) {
    throw err;
  }

  console.log(idm); // show read IDm
});
```
