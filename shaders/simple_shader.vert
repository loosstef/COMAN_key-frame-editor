#version 400

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexColor;

out vec3 color;
out vec3 fragPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform int id;

void main() {
    if(id == 0) {
        color = vertexColor, 1.0f;
    }
    else {
        int r = (id & 0x000000FF) >>  0;
        int g = (id & 0x0000FF00) >>  8;
        int b = (id & 0x00FF0000) >> 16;
        color = vec3(r/255.0, g/255.0, b/255.0);
    }
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1.0);
    fragPos = vec3(modelMatrix * vec4(vertexPos, 1.0));
}