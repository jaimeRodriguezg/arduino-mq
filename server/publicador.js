const mqtt = require('mqtt');
const argv = require('.././config/yargs').argv;

const client  = mqtt.connect(`mqtt://${argv.ip}`);
client.on('connect', function () {
    setInterval(function() {
        client.publish('myTopic', 'Hello mqtt');
        console.log('Message Sent');
    }, 5000);
});