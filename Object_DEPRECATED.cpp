//
// Created by stef on 02.03.20.
//

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Object_DEPRECATED.h"

const int POINT_COORD_DATASIZE = 3;
const int POINT_COLOR_DATASIZE = 3;
const int POINT_DATASIZE = POINT_COORD_DATASIZE + POINT_COLOR_DATASIZE;

/**
 * Constructor
 * @param points
 * @param pointsCount
 * @param mode
 */
Object_DEPRECATED::Object_DEPRECATED(float *points, int pointsCount, GLenum mode) :
    mPoints(points), mPointsCount(pointsCount), mMode(mode) {
}


void Object_DEPRECATED::loadToGPU(int pointsLayout, int colorLayout) {
    // generate vbo
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, POINT_DATASIZE * mPointsCount * sizeof(float), mPoints, GL_STATIC_DRAW);
    // generate vao
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(pointsLayout, POINT_COORD_DATASIZE, GL_FLOAT, GL_FALSE, POINT_DATASIZE*sizeof(float), NULL);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(colorLayout, POINT_COLOR_DATASIZE, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*) (POINT_COORD_DATASIZE * sizeof(GLfloat)));
    glEnableVertexAttribArray(pointsLayout);
    glEnableVertexAttribArray(colorLayout);
}


void Object_DEPRECATED::draw(GLint uniTrans, glm::mat4 modelMat) {
    glBindVertexArray(mVAO);
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(mMode, 0, mPointsCount);
}
