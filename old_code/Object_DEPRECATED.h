//
// Created by stef on 02.03.20.
//

#ifndef ANTONGERDELAN_OBJECT_H
#define ANTONGERDELAN_OBJECT_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/detail/type_mat.hpp>
#include <string>

class Object_DEPRECATED {
public:
    Object_DEPRECATED(float* points = nullptr, int pointsCount = 0, GLenum mode = GL_TRIANGLES);
    void loadToGPU(int pointsLayout = 0, int colorLayout = 1);
    void draw(GLint uniTrans, glm::mat4 modelMat = glm::mat4(1.0f));

protected:
    float *mPoints;
    int mPointsCount;

private:
    GLenum mMode;
    GLuint mVBO = 0;
    GLuint mVAO = 0;
};


#endif //ANTONGERDELAN_OBJECT_H
