const http = require('http');
const express = require('express');
const SocketIO = require('socket.io');
const mqtt = require('mqtt');
const argv = require('.././config/yargs').argv;
const color = require('colors'); 

app = express();
const server = http.createServer(app);

const path = require('path');
const publicPath = path.resolve(__dirname, '../public');
app.use(express.static(publicPath));


const io = SocketIO.listen(server);
io.on('connection', (client) => {
    console.log('========= Usuario conectado ========='.red);
})

const client  = mqtt.connect(`mqtt://${argv.ip}`);
client.on('connect', function () {
    client.subscribe('myTopic')
    console.log("========= ip servidor =========".yellow);
    console.log(`${argv.ip}`.yellow);
    console.log('==============================='.yellow);
})
client.on('message', function (topic, message) {
    context = message.toString();
    console.log(context);
    console.log(message);
    io.emit('data', context);
    //console.log('hola');
});



server.listen(3000, () => {
    console.log('========= Server web escuchando en el puerto ========='.green);
    console.log("3000".green);
    console.log(`${server.address()}`.green);
});