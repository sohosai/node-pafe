var pafe = require('bindings')('pafe');
module.exports = pafe;

pafe.readIDm(function (err, idm) {
  console.log(err, idm);
});

console.log('hello');
