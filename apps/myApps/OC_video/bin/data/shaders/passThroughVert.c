// vertex shader

#version 410

in vec2 texcoord;
in vec4 position;
out vec2 texcoordVarying;
//parameter passed from openFrameworks
uniform mat4 modelViewProjectionMatrix;

void main()
{   
	texcoordVarying = texcoord;
    // send the vertices to the fragment shader
	gl_Position = modelViewProjectionMatrix * position;
}