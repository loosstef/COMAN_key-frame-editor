#version 400

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;
layout(location = 2) in vec3 vertex_normal;

out vec3 colour;
out vec3 normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
  colour = vertex_colour;
  gl_Position = proj * view * model * vec4(vertex_position, 1.0);
  normal = vertex_normal;
  FragPos = vec3(model * vec4(vertex_position, 1.0));
}