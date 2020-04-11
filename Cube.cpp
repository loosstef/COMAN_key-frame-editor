//
// Created by stef on 02.03.20.
//

#include "Cube.h"

const int POINTS_COUNT = 36;

Cube::Cube(float size) {
    // todo: adapt cube size to given size
    mPoints = new float[6*6*6] {
                // BACK
                -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                // FRONT
                -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
                0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
                0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
                -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
                // LEFT
                -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                // RIGHT
                0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
                0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
                0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
                // BOTTOM
                -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
                0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
                0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
                // TOP
                -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
                0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };
    mPointsCount = POINTS_COUNT;
}
