// fragment shader
#version 410

in vec2 texCoordVarying;

//get this one for free by calling bind on a texture
uniform sampler2DRect texture0;
out vec4 outputColor;

// would need to be passed from geometry shader
// in vec2 texCoordVarying;
in vec4 color;

//the origin for the gl_FragCoord by default starts in the lower left
//this sets it to the upper left
layout(origin_upper_left) in vec4 gl_FragCoord;

void main()
{

    outputColor = color;

}