#version 400

in vec3 color;
in vec3 fragPos;

out vec4 fragColor;

void main() {
    fragColor = vec4(color, 1.0f);
}
