// vertex shader
#version 410
uniform mat4 modelViewProjectionMatrix;
in vec4 position;

void main(){
    //just calculate the position and pass it on
    gl_Position = modelViewProjectionMatrix * position;
}