#include <stdlib.h>
#include <stdio.h>

#include "esUtil.h"
#include "gl-utils.h"

// Draw a square using the shader pair created in Init()
void DrawSquare(ESContext* esContext) {
    GLfloat vVertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
    };
    GLfloat vColors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
    };

    // Call gl-utils's DrawShape function
    DrawShape(esContext, GL_TRIANGLE_STRIP, vVertices, 3, GL_FLOAT, vColors, 4, GL_FLOAT, 4);
}

int main(int argc, char* argv[]) {
    ESContext esContext;
    UserData userData;

    esInitContext(&esContext);
    esContext.userData = &userData;

    esCreateWindow(&esContext, "Hello Square", 320, 240, ES_WINDOW_RGB);

    if (!Init(&esContext)) {
        perror("Init context");
        return 1;
    }

    esRegisterDrawFunc(&esContext, DrawSquare);

    esMainLoop(&esContext);

    return 0;
}
