//
// Created by stef on 20.04.20.
//

#ifndef PROJECT_STANDARDSHADER_H
#define PROJECT_STANDARDSHADER_H


#include "Shader.h"

enum MatrixType {TRANSFORMATION_MATRIX, VIEW_MATRIX, PROJECTION_MATRIX};

class StandardShader : public Shader {
public:
    StandardShader();
    void setMatrix(MatrixType matType, glm::mat4 &mat);
    void setId(int id);
    GLint getUniLocTexture();
private:

};


#endif //PROJECT_STANDARDSHADER_H
