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
    Shader(char *vsPath, char *fsPath, std::string name);
    GLint getUniLoc(const char *name);
    void use();
    void setMat4(std::string varName, glm::mat4 mat);
    std::string getName() { return mName; }
protected:
    const std::string mName;
private:
    GLint mProgram;
};


#endif //PROJECT_SHADER_H
