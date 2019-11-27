//Mosca
const mosca = require('mosca')
const settings = {
   http: {
    // port for websockets, MQTT is running in default port 1883
    port: 8000,
    bundle: true,
    static: '../public'
  }
}
// start mosca
const moscaServer = new mosca.Server(settings);
moscaServer.on('ready', setup);

// fired when the mqtt server is ready
function setup() {
    console.log('Mosca server is up and running in port 1883!')
    console.log('Using port 8000 for MQTT over Web-Sockets!')
}

moscaServer.on('clientConnected', () => {
    console.log('client connected');
});

