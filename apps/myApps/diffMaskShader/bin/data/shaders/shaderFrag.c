// fragment shader
#version 410

uniform sampler2DRect mask;
uniform sampler2DRect top;

uniform float time; //Parameter which we will pass from OF

out vec4 outputColor;

//the origin for the gl_FragCoord by default starts in the lower left
//this sets it to the upper left
// layout(origin_upper_left) in vec4 gl_FragCoord;

void main()
{
    //extract just the x and y values from the current fragmentCoordinates. normally xyzw
    vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y);
    
    //get sample color from texture
    vec4 topColor = texture(top, pos);
    vec4 maskColor = texture(mask, pos);

    outputColor = vec4(topColor.rgb, 1.0 - maskColor.r);
    // outputColor = vec4(topColor.rgb, maskColor.r);
}