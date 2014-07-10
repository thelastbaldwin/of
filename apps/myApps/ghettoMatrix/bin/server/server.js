// oF application must be running before this
var express = require('express'),
	app = express(),
	http = require('http').Server(app),
	io = require('socket.io')(http),
	dgram = require('dgram'),
	osc = require('osc-min'),
	// osc is a thin layer on top of udp
	sendSocket = dgram.createSocket('udp4'),
	recieveSocket = dgram.createSocket('udp4'),
	SEND_PORT = 12345,
	RECIEVE_PORT = 12346;

sendSocket.bind(SEND_PORT);
recieveSocket.bind(RECIEVE_PORT);

function getOSCMessage(msg){
	var oscMessage = osc.fromBuffer(msg);

	try{
		//translate osc buffer into javascript object
		var element = oscMessage.elements[0],
		address = element.address,
		args = element.args; //contains 'type' and 'value

		return {
			filename: args[0].value,
			id : args[1].value
		}

	}catch(error){
		console.log("invalid OSC packet");
	}
}

function sendOSCMessage(photoType, socketId){
	var buffer = osc.toBuffer({
		address: '/take/picture',
		args : [{
			type: "string",
			value: photoType
		},
		{
			type: "string",
			value: socketId
		}]
	});

	sendSocket.send(buffer, 0, buffer.length, SEND_PORT, 'localhost');
}

recieveSocket.on('message', function(message, remote){
	if (address = '/transmit/photo') {
		var messageValues = getOSCMessage(message);
		io.sockets.to(messageValues.id).emit('transmit photo', messageValues.filename);
	}
});

// express setup
app.use("/js", express.static(__dirname + '/js'));
app.use("/css", express.static(__dirname + '/css'));
//this should be the data folder for the oF app
app.use("/img", express.static(__dirname + '/../data'));



//websockets
io.on('connection', function(socket){
	console.log('a user connected');

	socket.on('take photo', function(message){
		console.log('take photo', message, socket.id);
		sendOSCMessage(message.type, socket.id);
	});

	socket.on('disconnect', function(){
		console.log('a user disconnected');
	});
});

app.get('/', function(req, res){
	res.sendfile(__dirname + '/views/index.html');
});

http.listen(3000, function() {
    console.log('Listening on port', http.address().port);
});