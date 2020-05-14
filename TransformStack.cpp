//
// Created by stef on 30.04.20.
//

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "TransformStack.h"
#include "RenderEngine.h"
#include "Shader.h"

TransformStack::TransformStack(RenderEngine *renderEngine)
{
    mRenderEngine = renderEngine;
    mStack.emplace(1.0f);
}

/**
 * Push new transformation on stack and update the transformation matrix
 * to the new combination.
 * @param transMat
 */
void TransformStack::push(glm::mat4 transMat) {
    glm::mat4 newTopMat = mStack.top() * transMat;
    mStack.push(newTopMat);
    Shader *shader = mRenderEngine->shader();
    GLint uniLocTransMat = shader->getUniLoc(TRANSFORMATION_MATRIX_VAR_NAME);
    glUniformMatrix4fv(uniLocTransMat, 1, GL_FALSE, glm::value_ptr(newTopMat));
}


void TransformStack::pop() {
    if(mStack.size() <= 1) {
        std::cerr << "Transformation Stack is already at lowest level, can't be popped." << std::endl;
        exit(1);
    }
    mStack.pop();
}

glm::mat4 TransformStack::top() {
    return mStack.top();
}
