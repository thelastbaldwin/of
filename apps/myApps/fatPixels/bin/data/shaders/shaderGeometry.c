// geometry shader
#version 410

uniform mat4 modelViewProjectionMatrix;

layout(points) in;
layout(points, max_vertices=1) out;
// layout(triangle_strip, max_vertices=4) out;

in VertexData {
    vec2 texCoord;
    vec4 color;
    vec3 normal;
} VertexIn[1];

out vec4 color;

void main(){
	color = VertexIn[0].color;

	//want to replace this vertex with a quad
	gl_Position = modelViewProjectionMatrix * gl_in[0].gl_Position;
	EmitVertex();
	EndPrimitive();
}