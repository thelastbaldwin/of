var dgram = require('dgram'),
	Keen = require('keen-js'),
	osc = require('osc-min'),
	receiveSocket = dgram.createSocket('udp4'),
	RECEIVE_PORT = 12345;

var keen = new Keen({
	projectId: "54c96d4359949a31d51bc572",
	writeKey: "3719ff6af2c1ece0aa186ac872140d5d4ea07a797f44585fb7a9583b4f1342e14c686240bf1867f0f10a6ddc51b982f8bd3fef9dbddb115ad5f3f4aee9924ded7c7a7ec5efbe729af3e7999fc6110fd802c796f0b3442b7b095d2669a34e50a9f3b3c02fe85a7165bef3d8a1e3ad72e7"
});

receiveSocket.bind(RECEIVE_PORT);

receiveSocket.on('message', function(message){
	var oscMessage = osc.fromBuffer(message);

	if(oscMessage.elements[0].address === '/heartbeat'){
		var now = getDateTime();
		console.log("still_alive: " + now);
		keen.addEvent('test', {visualization_still_alive: true}, function(err, res){
			if(err){
				console.log("error: " + err);
			}
		});
	}
});

function getDateTime() {
	var date = new Date();
	var hour = date.getHours();
	hour = (hour < 10 ? "0" : "") + hour;

	var min  = date.getMinutes();
	min = (min < 10 ? "0" : "") + min;

	var sec  = date.getSeconds();
	sec = (sec < 10 ? "0" : "") + sec;

	var year = date.getFullYear();

	var month = date.getMonth() + 1;
	month = (month < 10 ? "0" : "") + month;

	var day  = date.getDate();
	day = (day < 10 ? "0" : "") + day;

	return year + ":" + month + ":" + day + ":" + hour + ":" + min + ":" + sec;
}