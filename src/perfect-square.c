#include <stdlib.h>
#include <stdio.h>

#include "esUtil.h"
#include "gl-utils.h"

// Draw a square using the shader pair created in Init()
void DrawPerfectSquare(ESContext* esContext) {
    GLfloat vVertices[] = {
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
    };
    GLfloat vColors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
    };

    // Call gl-utils's SetViewport function
    SetViewport(esContext);

    // Call gl-utils's ClearScreen function
    ClearScreen(0.0f, 0.0f, 0.0f, 1.0f);

    // Call gl-util's ProjectShape function
    ProjectShape(esContext, "modelViewProjection");

    // Call gl-utils's DrawShape function
    DrawShape(esContext, GL_TRIANGLE_STRIP, vVertices, 3, GL_FLOAT, vColors, 4, GL_FLOAT, 4);
}

void HandleWindowResize(ESContext* esContext, int width, int height) {
    printf("window has resized to %dx%d\n", width, height);

    esContext->width = width;
    esContext->height = height;
}

int main(int argc, char* argv[]) {
    ESContext esContext;
    UserData userData;

    if (Init(&esContext, &userData, "Hello Perfect Square", 320, 240, ES_WINDOW_RGB, DrawPerfectSquare, NULL, NULL, HandleWindowResize, "shaders/basic-color-transform.vs", "shaders/basic.fs"))
    {
        perror("Init context");
        return 1;
    }

    Run(&esContext);

    return 0;
}
