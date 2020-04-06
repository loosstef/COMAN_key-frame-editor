//
// Created by stef on 25.02.20.
//

#include "Lights.h"

Lights::Lights() {
    // contains data of all lights:
    // pos[3], ambient[3], diffuse[3], specular[3]
    lights = new float[SIZE_OF_LIGHT * MAX_AMOUNT_OF_LIGHTS]{
            0.0f, 0.0f, 0.0f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.8f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };
}

void Lights::sendToGPU(GLuint shader_program) {
    GLint uniPointLights = glGetUniformLocation(shader_program, UNIFORM_LIGHTPOINTS_NAME);
    glUniform1fv(uniPointLights, SIZE_OF_LIGHT * MAX_AMOUNT_OF_LIGHTS, lights);
}

void Lights::setPos(int index, float x, float y, float z) {
    lights[SIZE_OF_LIGHT*index] = x;
    lights[SIZE_OF_LIGHT*index+1] = y;
    lights[SIZE_OF_LIGHT*index+2] = z;
}

void Lights::setAmbientColor(int index, float r, float g, float b) {
    lights[SIZE_OF_LIGHT*index+3] = r;
    lights[SIZE_OF_LIGHT*index+4] = g;
    lights[SIZE_OF_LIGHT*index+5] = b;
}

void Lights::setDiffuseColor(int index, float r, float g, float b) {
    lights[SIZE_OF_LIGHT*index+6] = r;
    lights[SIZE_OF_LIGHT*index+7] = g;
    lights[SIZE_OF_LIGHT*index+8] = b;
}

void Lights::setSpecularColor(int index, float r, float g, float b) {
    lights[SIZE_OF_LIGHT*index+9] = r;
    lights[SIZE_OF_LIGHT*index+10] = g;
    lights[SIZE_OF_LIGHT*index+11] = b;
}