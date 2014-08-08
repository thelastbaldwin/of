// geometry shader
#version 410

uniform mat4 modelViewProjectionMatrix;

layout(points) in;
//layout(points, max_vertices=1) out;
 layout(triangle_strip, max_vertices=4) out;

in VertexData {
    vec2 texCoord;
    vec4 color;
    vec3 normal;
} VertexIn[1];

out vec4 color;

void main(){
	color = VertexIn[0].color;
	float squareSize = 16.0;

	//want to replace this vertex with a quad
	vec4 newPos;
	newPos = gl_in[0].gl_Position - vec4(squareSize, squareSize, 0.0, 0.0);
	gl_Position = modelViewProjectionMatrix * newPos;
	EmitVertex();
	newPos = gl_in[0].gl_Position - vec4(squareSize, -squareSize, 0.0, 0.0);
	gl_Position = modelViewProjectionMatrix * newPos;
	EmitVertex();
	newPos = gl_in[0].gl_Position + vec4(squareSize, -squareSize, 0.0, 0.0);
	gl_Position = modelViewProjectionMatrix * newPos;
	EmitVertex();
	newPos = gl_in[0].gl_Position + vec4(squareSize, squareSize, 0.0, 0.0);
	gl_Position = modelViewProjectionMatrix * newPos;
	EmitVertex();
		// gl_Position = modelViewProjectionMatrix * gl_in[0].gl_Position;
	// gl_Position = modelViewProjectionMatrix * gl_in[0].gl_Position;
	
	EndPrimitive();
}