// fragment shader

#version 410

out vec4 outputColor;
uniform float time, speed, lineThickness;

#define WHITE vec4(1.0, 1.0, 1.0, 1.0)

void main() {
  float thickness = max(lineThickness, 1);

  vec2 position = vec2(gl_FragCoord.x, gl_FragCoord.y);
  position.x += time * speed;
  float remainder = floor((position.x + position.y)/thickness);

  if(mod(remainder, 2.0) == 0.0){
    outputColor = WHITE;
  }else{
    discard;
  }
}