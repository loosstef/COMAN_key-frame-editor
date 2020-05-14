#version 400
in vec3 colour;
in vec3 normal;
in vec3 FragPos;

uniform float pointLights[10*12];

out vec4 frag_colour;

const int MAX_AMOUNT_OF_LIGHTS = 10;
const int DATA_PER_LIGHT = 12;

void main() {
  // AMBIENT COLOR

  // DIFFUSE COLOR
  vec3 norm = normalize(normal);
  vec3 diffuse = vec3(0.0f, 0.0f, 0.0f);
  vec3 ambient = vec3(0.0f, 0.0f, 0.0f);
  for(int i = 0; i < 10; ++i) {
    vec3 lightPos = vec3(pointLights[DATA_PER_LIGHT*i], pointLights[DATA_PER_LIGHT*i+1], pointLights[DATA_PER_LIGHT*i+2]);
    // AMBIENT COLOR
    vec3 ambientLightColor = vec3(pointLights[DATA_PER_LIGHT*i+3], pointLights[DATA_PER_LIGHT*i+4], pointLights[DATA_PER_LIGHT*i+4]);
    ambient = ambient + ambientLightColor;
    // DIFFUSE COLOR
    vec3 diffuseLightColor = vec3(pointLights[DATA_PER_LIGHT*i+6], pointLights[DATA_PER_LIGHT*i+7], pointLights[DATA_PER_LIGHT*i+8]);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    diffuse = diffuse + diff * diffuseLightColor;
  }

  // PHONG LIGHTING
  vec3 resultColour = (ambient + diffuse) * colour;
  frag_colour = vec4(resultColour, 1.0f);
}