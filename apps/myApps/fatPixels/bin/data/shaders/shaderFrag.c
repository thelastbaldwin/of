// fragment shader
#version 410

//get this one for free by calling bind on a texture
uniform sampler2DRect texture0;
out vec4 outputColor;

// would need to be passed from geometry shader
// in vec2 texCoordVarying;
in VertexData {
    vec2 texCoord;
    vec4 color;
} Vertex;

//the origin for the gl_FragCoord by default starts in the lower left
//this sets it to the upper left
layout(origin_upper_left) in vec4 gl_FragCoord;

void main()
{
    //extract just the x and y values from the current fragmentCoordinates. normally xyzw
    //vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y);
    
	//updated texture coordinate from vertex shader
    //vec2 pos = texCoordVarying;

    //outputs the color of the texture at the updated position
    //outputColor = texture(texture0, pos);
    outputColor = Vertex.color;
    
    //output black
    //outputColor = vec4(0.0, 0.0, 0.0, 1.0);
}