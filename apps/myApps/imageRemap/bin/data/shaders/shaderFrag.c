// fragment shader
#version 410

uniform sampler2DRect texture0;
uniform sampler2DRect forest;	
uniform sampler2DRect mappedColors;

out vec4 outputColor;

int getBrightnessIndex(vec4 inputColor){
	return int(dot(inputColor, vec4(0.25) * 255));
}

// vec4 getOrderedColor(vec2 pos){
// 	//
// }

//the origin for the gl_FragCoord by default starts in the lower left
//this sets it to the upper left
layout(origin_upper_left) in vec4 gl_FragCoord;
// in vec4 gl_FragCoord;

void main(){
    //extract just the x and y values from the current fragmentCoordinates
    vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y);

    vec4 inputColor = texture(forest, pos);
    int index = getBrightnessIndex(inputColor);

    outputColor = texture(mappedColors, vec2(index, 0));
}