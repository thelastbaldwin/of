// vertex shader
#version 410
uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec2 texcoord;

uniform sampler2DRect texture0;
uniform float time;

out vec2 texCoordVarying;

void main(){
    //this is the normal method for calculating the current vertex position
    vec4 modifiedPosition = position;

    //this should be adjustable from the main application
    float scale = 100;

    //not strictly based on brightness, just one channel
    float displacementZ = texture(texture0, texcoord).r;

    modifiedPosition.z += displacementZ * scale;

    gl_Position = modelViewProjectionMatrix * modifiedPosition;
    texCoordVarying = vec2(modifiedPosition.x + texcoord.x, modifiedPosition.y + texcoord.y);
}