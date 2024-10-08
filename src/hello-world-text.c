#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "esUtil.h"
#include "gl-utils.h"

// Draw a triangle using the shader pair created in Init()
void DrawHelloWorldText(ESContext* esContext) {
    // Call gl-utils's SetViewport function
    SetViewport(esContext);

    // Call gl-utils's ClearScreen function
    ClearScreen(0.0f, 0.0f, 0.0f, 1.0f);

    // Call gl-utils's DrawShape function
    DrawTextString(esContext, "HELLO WORLD", -0.5f, 0.5f, 0.01f);
}

int main(int argc, char* argv[]) {
    ESContext esContext;
    UserData userData;

    if (Init(&esContext, &userData, "Hello World Text String!", 1280, 480, ES_WINDOW_RGB, DrawHelloWorldText, NULL, NULL, NULL, "shaders/text-vert.glsl", "shaders/text-frag.glsl")) {
        perror("Init context");
        return 1;
    }

    Run(&esContext);

    return 0;
}
