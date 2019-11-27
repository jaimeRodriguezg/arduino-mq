var mqtt = require('mqtt');

// connect to the Moscar broker server
const client  = mqtt.connect('ws:0.0.0.0:8000') // your broker server ip here

client.on('connect', function () {
  //subscribe to listen to the channels in which arduinos will be publishing
  client.subscribe('/exampleTopic')
})

client.on('message', (topic, message) => {
	console.log('topic: ', topic)
  console.log('message: ', message)
})
