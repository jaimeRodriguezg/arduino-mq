const mosca = require('mosca');
const color = require('colors');

const settings = {
		port:1883
		}

var server = new mosca.Server(settings);

server.on('ready', function(){
    console.log("ready".yellow);
});

server.on('clientConnected', (client) => {
	console.log('cliente conectado'.green);
})