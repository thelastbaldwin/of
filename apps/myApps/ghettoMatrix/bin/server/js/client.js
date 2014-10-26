var socket = io();
var container = document.getElementsByClassName('container')[0];
var img = document.getElementsByTagName('img')[0];
var IMGPATH = 'img/output/';

// DOM events
container.addEventListener('click', function(e){
	if(event.srcElement.type === "button") {
		socket.emit('take photo', { type : e.srcElement.value});
	}
	e.stopPropagation();
}, false);

// socket events
socket.on('transmit photo', function(filename){
	console.log(filename);
	img.setAttribute('src', IMGPATH + filename);
});