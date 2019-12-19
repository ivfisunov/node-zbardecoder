const fs = require('fs');
const path = require('path');
const util = require('util');
const barcode = require('../');

fs.readdir = util.promisify(fs.readdir);

(async function () {

  const files = await fs.readdir('img');
  files.map(file => {
    const filePath = path.join('img', file);
    const result = JSON.parse(barcode.decode(filePath));
    console.log(file);
    console.log(result, '\n');
  });

})();