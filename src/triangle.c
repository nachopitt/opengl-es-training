#include <stdlib.h>
#include <stdio.h>

#include "esUtil.h"
#include "gl-utils.h"

// Draw a triangle using the shader pair created in Init()
void DrawTriangle(ESContext* esContext) {
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

    // Call gl-utils's SetViewport function
    SetViewport(esContext);

    // Call gl-utils's ClearScreen function
    ClearScreen(0.0f, 0.0f, 0.0f, 1.0f);

    // Call gl-utils's DrawShape function
    DrawShape(esContext, GL_TRIANGLES, vVertices, 3, GL_FLOAT, vColors, 4, GL_FLOAT, 3);
}

int main(int argc, char* argv[]) {
    ESContext esContext;
    UserData userData;

    if (Init(&esContext, &userData, "Hello Triangle", 320, 240, ES_WINDOW_RGB, DrawTriangle, NULL, NULL, NULL, "shaders/basic-color.vs", "shaders/basic.fs")) {
        printf("Context initialization failed\n");
        return 1;
    }

    Run(&esContext);

    return 0;
}
