//
// Created by stef on 03.03.20.
//

#include <iostream>
#include "Path_old.h"


Path_old::Path_old(float *points, int pointsCount, GLenum mode) : Object(points, pointsCount, mode) {

}


glm::vec3 Path_old::valueArcLength(float g) {
    if(g == 1.0f) {
        return valueParametric(1.0f);
    }
    uint lowerIndex = locateClosestArcLength(g);
    uint higherIndex = lowerIndex+1;
    float lowerArcLength = mArcLengthTable[lowerIndex];
    float higherArcLength = mArcLengthTable[higherIndex];
    float lowerU = mTableStepSize * lowerIndex;
    float higherU = mTableStepSize * higherIndex;
    float factor = (g-lowerArcLength) / (higherArcLength-lowerArcLength);
    float u = lowerU + factor * (higherU-lowerU);
    return valueParametric(u);
}

/**
 * Populate the arc length table
 * @param stepCount
 */
void Path_old::populateArcLengthTable(uint stepCount) {
    mTableStepSize = 1.0f / stepCount;
    float currArcLength = 0.0f;
    mArcLengthTable.push_back(currArcLength);
    glm::vec3 lastArcPoint = valueParametric(0.0f);
    for(int i = 1; i <= stepCount; ++i) {
        float u = (float)i / (float)stepCount;
        glm::vec3 currArcPoint = valueParametric(u);
        currArcLength += dist(lastArcPoint, currArcPoint);
        mArcLengthTable.push_back(currArcLength);
        lastArcPoint = currArcPoint;
    }
    // normalize all values
    for(int i = 1; i < stepCount; ++i) {
        mArcLengthTable[i] /= currArcLength;
    }
}


/**
 * Calculate the distance between 2 points in 3-dimensional space.
 * @param v1 point 1
 * @param v2 point 2
 * @return the distance
 */
float Path_old::dist(glm::vec3 v1, glm::vec3 v2) {
    return sqrtf(powf(v1.x-v2.x, 2) + powf(v1.y-v2.y, 2) + powf(v1.z-v2.z, 2));
}


/**
 * Locate the index of the arc length which is closest to a given arc length in the arc-length-table
 * @param arcLength the searched for arc length
 * @return the index of the arc length which is closest to the given one
 */
uint Path_old::locateClosestArcLength(float arcLength) {
    int closestIndex;
    float closestArcDist = INFINITY;
    for(int i = 0; i < mArcLengthTable.size(); ++i) {
        float dist = arcLength - mArcLengthTable[i];
        if(dist < 0) {
            break;
        }
        if(dist < closestArcDist) {
            closestIndex = i;
            closestArcDist = dist;
        }
    }
    return closestIndex;
}
