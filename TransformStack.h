//
// Created by stef on 30.04.20.
//

#ifndef PROJECT_TRANSFORMSTACK_H
#define PROJECT_TRANSFORMSTACK_H

#include <stack>
#include <glm/detail/type_mat.hpp>

class RenderEngine;

class TransformStack {
public:
    TransformStack(RenderEngine *renderEngine);
    void push(glm::mat4 transMat);
    void pop();
    glm::mat4 top();
private:
    RenderEngine* mRenderEngine;
    std::stack<glm::mat4> mStack;
    // constants
    const char TRANSFORMATION_MATRIX_VAR_NAME[17] = "projectionMatrix";

};


#endif //PROJECT_TRANSFORMSTACK_H
