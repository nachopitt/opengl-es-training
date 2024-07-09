#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "esUtil.h"
#include "gl-utils.h"

// Draw a triangle using the shader pair created in Init()
void DrawTriangle(ESContext* esContext) {
    // Rotation angle
    static GLfloat angle = 0.0f;
    GLfloat x_distance = 0.0f;
    float speed_factor = 2.0f;
    // Get time in seconds
    float time = GetCurrentTimeInSeconds();

    GLfloat vVertices[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };
    GLfloat vColors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
    };

    // Set up rotation angle
    // Example: Rotate 1 degree per frame
    angle += 1.0f;
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }

    // Setup translation distance in x axis
    // Move along the x-axis with a sine wave, scaling to keep within bounds
    x_distance = sin(time * speed_factor) * 0.5f;

    // Call gl-utils's TransformShape function
    TransformShape(esContext, angle, x_distance, "modelViewProjection");

    // Call gl-utils's DrawShape function
    DrawShape(esContext, GL_TRIANGLES, vVertices, 3, GL_FLOAT, vColors, 4, GL_FLOAT, 3);
}

int main(int argc, char* argv[]) {
    ESContext esContext;
    UserData userData;

    if (Init(&esContext, &userData, "Hello Triangle", 320, 240, ES_WINDOW_RGB, DrawTriangle, "shaders/basic-color-rotate.vs", "shaders/basic.fs")) {
        perror("Init context");
        return 1;
    }

    Run(&esContext);

    return 0;
}
