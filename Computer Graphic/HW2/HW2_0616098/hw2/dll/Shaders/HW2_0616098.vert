#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texture;

out vec2 texcoord;

uniform mat4 Projection;
uniform mat4 ModelView;

void main() {
  // the final rendered position of vertex
  gl_Position = Projection * ModelView * vec4(position, 1.0);
  texcoord = texture;
}
