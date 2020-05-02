//
// Created by stef on 20.04.20.
//

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Shader.h"
#include "InputHandler.h"

//char VERTEX_SHADER_FILENAME[] = "shaders/new_shader.vert";
//char FRAGMENT_SHADER_FILENAME[] = "shaders/new_shader.frag";

Shader::Shader(char *vsPath, char *fsPath) {
    GLuint vs = InputHandler::loadAndCompileShader(&vsPath[0], GL_VERTEX_SHADER);
    GLuint fs = InputHandler::loadAndCompileShader(&fsPath[0], GL_FRAGMENT_SHADER);
    mProgram = glCreateProgram();
    glAttachShader(mProgram, fs);
    glAttachShader(mProgram, vs);
    glLinkProgram(mProgram);
    glUseProgram(mProgram);
}

GLint Shader::getUniLoc(const char *name) {
    return glGetUniformLocation(mProgram, name);
}
