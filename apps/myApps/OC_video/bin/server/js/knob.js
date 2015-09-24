function Knob(elem, scale){
	this.elem = elem;
	this.label = elem.querySelector('.label');
	this.dial = elem.querySelector('.dial');
	this.input = elem.querySelector('input');
	this.max = parseFloat(this.input.max);
	this.min = parseFloat(this.input.min);
	this.scale = scale;

	this.dial.onmousedown = function(originalEvent){
		document.onmousemove = function(event){
			var original = {
				x: originalEvent.clientX,
				y: originalEvent.clientY
			};
			var current = {
				x: event.clientX,
				y: event.clientY
			};
			var dx = original.x - current.x;
			var dy = original.y - current.y;
			var distance = this.distance(original.x, original.y, current.x, current.y);

			if(Math.abs(dx) > Math.abs(dy)){
				//lateral movement
				//moving right
				if(dx > 0){
					this.input.value = this.clamp(parseFloat(this.input.value) - distance * this.scale, this.min, this.max);
				}
				//moving left
				if(dx < 0){
					this.input.value = this.clamp(parseFloat(this.input.value) + distance * this.scale, this.min, this.max);
				}
			}else if(Math.abs(dx) < Math.abs(dy)){
				//vertical movement
				//moving up
				if(dy < 0){
					this.input.value = this.clamp(parseFloat(this.input.value) - distance * this.scale, this.min, this.max);
				}
				//moving left
				if(dy > 0){
					this.input.value = this.clamp(parseFloat(this.input.value) + distance * this.scale, this.min, this.max);
				}
			}
			this.setRotation(this.calculateRotation());
		}.bind(this);
		document.onmouseup = function(event){
			document.onmousemove = null;
		}.bind(this);
	}.bind(this);

	this.input.onchange = function(){
		this.setRotation(this.calculateRotation());
	}.bind(this);

	this.setRotation(this.calculateRotation());
}

Knob.prototype.clamp = function(value, min, max){
	if(value < min){
		return min;
	}else if(value > max){
		return max;
	}
	return value;
};

Knob.prototype.distance = function(x1, y1, x2, y2){
	return Math.sqrt(Math.pow(x1 - x2, 2) + Math.pow(y1 - y2, 2));
};

Knob.prototype.map_range = function(value, low1, high1, low2, high2) {
	//http://stackoverflow.com/questions/5649803/remap-or-map-function-in-javascript
	return low2 + (high2 - low2) * (value - low1) / (high1 - low1);
};

Knob.prototype.calculateRotation = function(){
	//map the input value between 0 and 360
	//depending on the range between input values
	return this.map_range(parseFloat(this.input.value), this.min, this.max, 0, 360);
};

Knob.prototype.setRotation = function(deg){
	this.dial.style.webkitTransform = this.dial.style.transform = 'rotate(' + deg + 'deg)';
};