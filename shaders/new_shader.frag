#version 400

//in vec3 color;
in vec3 fragPos;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

out vec4 fragColor;

void main() {
//    fragColor = vec4(color, 1.0f);
    fragColor = texture(texture_diffuse1, TexCoords);
}


//    #version 330 core
//out vec4 FragColor;
//
//in vec2 TexCoords;
//
//uniform sampler2D texture_diffuse1;
//
//void main()
//{
//    FragColor = texture(texture_diffuse1, TexCoords);
//}
