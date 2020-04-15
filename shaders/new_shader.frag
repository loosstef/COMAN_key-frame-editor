#version 400

//in vec3 color;
in vec3 fragPos;
in vec2 TexCoords;

uniform int id;
uniform sampler2D texture_diffuse1;

out vec4 fragColor;

void main() {
    if(id != 0) {
            int r = (id & 0x000000FF) >>  0;
            int g = (id & 0x0000FF00) >>  8;
            int b = (id & 0x00FF0000) >> 16;
            fragColor = vec4(r/255.0, g/255.0, b/255.0, 1.0);
    } else {
        fragColor = texture(texture_diffuse1, TexCoords);
    }
//    fragColor = vec4(color, 1.0f)
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
