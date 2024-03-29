#include <stdio.h>

#include "gl-utils.h"

// Draw a triangle using the shader pair created in Init()
void DrawTriangle(ESContext* esContext) {
    GLfloat vVertices[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    GLfloat vColors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
    };

    DrawShape(esContext, vVertices, 3, GL_FLOAT, vColors, 4, GL_FLOAT);
}

int main(int argc, char* argv[]) {
    ESContext esContext;
    UserData userData;

    esInitContext(&esContext);
    esContext.userData = &userData;

    esCreateWindow(&esContext, "Hello Triangle", 320, 240, ES_WINDOW_RGB);

    if (!Init(&esContext)) {
        perror("Init context");
        return 1;
    }

    esRegisterDrawFunc(&esContext, DrawTriangle);

    esMainLoop(&esContext);

    return 0;
}
