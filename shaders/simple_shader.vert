#version 400

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexColor;

out vec3 color;
out vec3 fragPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    color = vertexColor;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1.0);
    fragPos = vec3(modelMatrix * vec4(vertexPos, 1.0));
}