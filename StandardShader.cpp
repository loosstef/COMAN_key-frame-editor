//
// Created by stef on 20.04.20.
//

#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "StandardShader.h"

char VERTEX_SHADER_FILENAME[] = "shaders/new_shader.vert";
char FRAGMENT_SHADER_FILENAME[] = "shaders/new_shader.frag";

char PROJECTION_MATRIX_VAR_NAME[] = "projectionMatrix";
char VIEW_MATRIX_VAR_NAME[] = "viewMatrix";
char TRANSFORMATION_MATRIX_VAR_NAME[] = "modelMatrix";
char ID_VAR_NAME[] = "id";
char TEXTURE_VAR_NAME[] = "texture_diffuse1";

StandardShader::StandardShader() : Shader(VERTEX_SHADER_FILENAME, FRAGMENT_SHADER_FILENAME) {

}

void StandardShader::setMatrix(MatrixType matType, glm::mat4 &mat) {
    switch(matType) {
        case TRANSFORMATION_MATRIX: {
            GLint uniLocTransMat = getUniLoc(TRANSFORMATION_MATRIX_VAR_NAME);
            glUniformMatrix4fv(uniLocTransMat, 1, GL_FALSE, glm::value_ptr(mat));
            break;
        }
        case VIEW_MATRIX: {
            GLint uniLocViewMat = getUniLoc(VIEW_MATRIX_VAR_NAME);
            glUniformMatrix4fv(uniLocViewMat, 1, GL_FALSE, glm::value_ptr(mat));
            break;
        }
        case PROJECTION_MATRIX: {
            GLint uniLocProjMat = getUniLoc(PROJECTION_MATRIX_VAR_NAME);
            glUniformMatrix4fv(uniLocProjMat, 1, GL_FALSE, glm::value_ptr(mat));
            break;
        }
    }
}

void StandardShader::setId(int id) {
    GLint uniLocObjIdMat = getUniLoc(ID_VAR_NAME);
    glUniform1i(uniLocObjIdMat, id);
}

GLint StandardShader::getUniLocTexture() {
    return getUniLoc(TEXTURE_VAR_NAME);
}
