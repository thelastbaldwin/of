// fragment shader
#version 410

// should distort pixels horizontally along a vertical wave
// should place scanlines
// should have opacity applied from main app

uniform sampler2DRect texture0;
uniform sampler2DRect video;
uniform sampler2DRect scanlines;
uniform float time; //Parameter which we will pass from OF
uniform float amplitude;
uniform float wavelength;
uniform float speed;
uniform float opacity;

out vec4 outputColor;

//the origin for the gl_FragCoord by default starts in the lower left
//this sets it to the upper left
layout(origin_upper_left) in vec4 gl_FragCoord;

void main(){
    //extract just the x and y values from the current fragmentCoordinates
    vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y);

    //want the unmodified texture coordiniate
    vec2 originalPos = pos;
    
    //shift the x-position
    pos.x += amplitude * cos((pos.y + time * speed)/ wavelength); 

    vec4 scanlineColor = texture(scanlines, originalPos);
    
    //get sample color from texture
    vec4 sampleColor = texture(texture0, pos);
    //remove a proportional amount of color based on the scanline texture color
    sampleColor.rgb = sampleColor.rgb - sampleColor.rgb * scanlineColor.a;

    //color from video Texture
    vec4 movieColor = texture(video, originalPos);

    outputColor = vec4(sampleColor.rgb*opacity + movieColor.rgb*(1.0 - opacity), 1.0);
}