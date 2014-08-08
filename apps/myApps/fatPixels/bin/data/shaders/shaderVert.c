// vertex shader
#version 410
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;
in vec3 normal;

uniform sampler2DRect texture0;
uniform float time;

out VertexData{
    vec2 texCoord;
    vec4 color;
    vec3 normal;
} VertexOut;

void main(){
    VertexOut.texCoord = texcoord;
    VertexOut.color = texture(texture0, texcoord);
    VertexOut.normal = normal;

    //this should be adjustable from the main application
    float scale = 100;

    //not strictly based on brightness, just one channel
    float displacementZ = texture(texture0, texcoord).r;

    vec4 modifiedPosition = position;
    modifiedPosition.z += displacementZ * scale;

    // gl_Position = modelViewProjectionMatrix * modifiedPosition;
    // gl_Position = gl_Vertex;
    // pass the unmolested vertex to the geometry shader
    gl_Position = position;
}