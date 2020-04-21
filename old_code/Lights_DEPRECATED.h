//
// Created by stef on 25.02.20.
//

#ifndef ANTONGERDELAN_LIGHTS_H
#define ANTONGERDELAN_LIGHTS_H


#include <GL/glew.h>

class Lights_DEPRECATED {
public:
    Lights_DEPRECATED();
    void sendToGPU(GLuint shader_program);
    void setPos(int index, float x, float y, float z);
    void setAmbientColor(int index, float r, float g, float b);
    void setDiffuseColor(int index, float r, float g, float b);
    void setSpecularColor(int index, float r, float g, float b);
private:
    const int MAX_AMOUNT_OF_LIGHTS = 10;
    const int SIZE_OF_LIGHT = 12;
    const char UNIFORM_LIGHTPOINTS_NAME[12] = "pointLights";
    float *lights;
};


#endif //ANTONGERDELAN_LIGHTS_H
