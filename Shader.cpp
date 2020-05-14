//
// Created by stef on 20.04.20.
//

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Shader.h"
#include "InputHandler.h"

//char VERTEX_SHADER_FILENAME[] = "shaders/standard.vert";
//char FRAGMENT_SHADER_FILENAME[] = "shaders/standard.frag";

Shader::Shader(char *vsPath, char *fsPath, std::string name) : mName(name) {
    GLuint vs = InputHandler::loadAndCompileShader(&vsPath[0], GL_VERTEX_SHADER);
    GLuint fs = InputHandler::loadAndCompileShader(&fsPath[0], GL_FRAGMENT_SHADER);
    mProgram = glCreateProgram();
    glAttachShader(mProgram, fs);
    glAttachShader(mProgram, vs);
    glLinkProgram(mProgram);
}

GLint Shader::getUniLoc(const char *name) {
    return glGetUniformLocation(mProgram, name);
}

void Shader::use() {
    glUseProgram(mProgram);
}

void Shader::setMat4(std::string varName, glm::mat4 mat) {
    GLint uniLocTransMat = getUniLoc(varName.c_str());
    glUniformMatrix4fv(uniLocTransMat, 1, GL_FALSE, glm::value_ptr(mat));
}
