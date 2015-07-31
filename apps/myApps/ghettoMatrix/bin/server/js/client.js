var socket = io();
var container = document.getElementsByClassName('container')[0];
var modal = document.getElementById('modal-overlay');
var timer = document.getElementsByClassName('counter')[0];
var counterTags = document.getElementsByClassName('counter-tag');
var img = document.getElementsByTagName('img')[0];
var IMGPATH = 'img/';

// DOM events
container.addEventListener('click', function(e){
	if(event.srcElement.type === "button") {
		if(e.srcElement.value == "traditional"){
			var steps = 16;
			timer.innerHTML = '';
			modal.classList.remove('hide');

			for(var i = 0 ; i < counterTags.length; i++){
				counterTags[i].classList.add('hide');
			}
			var currentCounterTag = 0;
			var countdown = setInterval(function(){
				steps--;
				var currentCount = timer.innerHTML = steps % 4;
				if(currentCount === 0){
					counterTags[currentCounterTag].classList.remove('hide');
					socket.emit('take photo', { type : e.srcElement.value, index: currentCounterTag});
					currentCounterTag++;
				}
				if(steps < 1){
					setTimeout(function(){
						clearInterval(countdown);
						modal.classList.add('hide');
					}, 200);	
				}
			}, 1000);
	
		}else{
			socket.emit('take photo', { type : e.srcElement.value});
		}
	}
	e.stopPropagation();
}, false);

// socket events
socket.on('transmit photo', function(filename){
	console.log(filename);
	img.setAttribute('src', IMGPATH + filename);
});
