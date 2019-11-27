const http = require('http');
const express = require('express');
const SocketIO = require('socket.io');
const mqtt = require('mqtt');

app = express();
const server = http.createServer(app);

const path = require('path');
const publicPath = path.resolve(__dirname, '../public');
app.use(express.static(publicPath));


const io = SocketIO.listen(server);
io.on('connection', (client) => {
    console.log('========= Usuario conectado =========');
})

const client  = mqtt.connect('mqtt://192.168.1.112');
client.on('connect', function () {
    client.subscribe('myTopic')
})
client.on('message', function (topic, message) {
    context = message.toString();
    console.log(context);
    console.log(message);
    io.emit('data', context);
    //console.log('hola');
});



server.listen(3000, () => {
    console.log('========= Server escuchando en el puerto =========');
    console.log("3000");
    console.log("===SERVER ADRESS==",server.address());
});