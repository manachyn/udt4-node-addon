var udt4 = require('bindings')('udt4');

var client = new udt4.Client();
var server = new udt4.Server();

//console.log(client.connect(9000, 'my host'));
console.log(server);