//
// Created by stef on 30.03.20.
//

#include <glm/gtc/matrix_transform.hpp>
#include "CLink.h"
#include "CJoint.h"

CLink::CLink(float linkLength, float linkTwist) {
    mLinkLength = linkLength;
    mLinkTwist = linkTwist;

    mPoints[0] = glm::vec3(0.0f);
    mPoints[1] = glm::vec3(linkLength, 0.0f, 0.0f);
    mIndices[0] = 0;
    mIndices[1] = 1;

    setupLink();
}

void CLink::setupLink() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec3), &mPoints[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)nullptr);

    // TODO: check if posible to skip normals and texture coords

    glBindVertexArray(0);
}

void CLink::draw(StandardShader &shader) {
    glm::mat4 transMat(1.0f);
    if(mParentJoint != nullptr) {
        transMat = mParentJoint->transMat();
    }

    shader.setMatrix(TRANSFORMATION_MATRIX, transMat);
//    shader.setId(256*256*255);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);

//    shader.setId(0);
}

void CLink::setChild(CJoint *childJoint) {
    mChildJoint = childJoint;
    float linkOffset = childJoint->offset();
    mPoints[1].z = linkOffset;
    setupLink();
}
