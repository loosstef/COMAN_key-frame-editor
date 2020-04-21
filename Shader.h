//
// Created by stef on 20.04.20.
//

#ifndef PROJECT_SHADER_H
#define PROJECT_SHADER_H

#include <GL/glew.h>
#include <string>
#include <glm/detail/type_mat.hpp>

class Shader {
public:
    Shader(char *vsPath, char *fsPath);
    GLint getUniLoc(char *name);
private:
    GLint mProgram;
};


#endif //PROJECT_SHADER_H
