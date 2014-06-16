// fragment shader
#version 410

uniform sampler2DRect mask;
uniform sampler2DRect top; //"top"

uniform float time; //Parameter which we will pass from OF

out vec4 outputColor;

float getAverage(vec3 color){
    //might be a better way to do this
    float total =  color.r + color.g + color.b;
    return total/3;
}

float polarize(float average){
    float threshold = 0.5;
    return (average < threshold)? 0.1 : 0.9;
}


void main()
{
    //extract just the x and y values from the current fragmentCoordinates. normally xyzw
    vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y);
    
    //get sample color from texture
    vec4 topColor = texture(top, pos);
    vec4 maskColor = texture(mask, pos);

    //polarize the masking value
    float maskValue = polarize(getAverage(maskColor.rgb));
    
    topColor = vec4(topColor.rgb, maskValue);
    
    outputColor = topColor;
}