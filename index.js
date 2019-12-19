const zbardecoder = require('bindings')('zbardecoder');

module.exports = {
  decode: zbardecoder.decode
}