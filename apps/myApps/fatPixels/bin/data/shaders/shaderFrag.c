// fragment shader
#version 410

//get this one for free by calling bind on a texture
uniform sampler2DRect texture;
out vec4 outputColor;

//the origin for the gl_FragCoord by default starts in the lower left
//this sets it to the upper left
layout(origin_upper_left) in vec4 gl_FragCoord;

void main()
{
    //extract just the x and y values from the current fragmentCoordinates. normally xyzw
    vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y);

    //outputs the color of the texture at the current position
    outputColor = texture(texture, pos);
}