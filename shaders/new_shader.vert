#version 400

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 aTexCoords;

//out vec3 color;
out vec3 fragPos;
out vec2 TexCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
//    int r = (id & 0x000000FF) >>  0;
//    int g = (id & 0x0000FF00) >>  8;
//    int b = (id & 0x00FF0000) >> 16;
//    color = vec3(r/255.0, g/255.0, b/255.0);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1.0);
    fragPos = vec3(modelMatrix * vec4(vertexPos, 1.0));
    TexCoords = aTexCoords;
}

//    #version 330 core
//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aNormal;
//layout (location = 2) in vec2 aTexCoords;
//
//out vec2 TexCoords;
//
//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
//
//void main()
//{
//    TexCoords = aTexCoords;
//    gl_Position = projection * view * model * vec4(aPos, 1.0);
//}
