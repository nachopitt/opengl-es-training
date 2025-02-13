#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    int width = 320;
    int height = 240;
#ifdef USE_DRM
    char device[] = "/dev/dri/card0";
#else
    char device[] = "";
#endif

    int option_arg_index = 1;
    while (option_arg_index < argc) {
        if (strcmp(argv[option_arg_index], "--width") == 0) {
            width = atoi(argv[++option_arg_index]);
        }
        else if (strcmp(argv[option_arg_index], "--height") == 0) {
            height = atoi(argv[++option_arg_index]);
        }
        else if (strcmp(argv[option_arg_index], "--device") == 0) {
            option_arg_index++;
            snprintf(device, strlen(argv[option_arg_index]) + 1, "%s", argv[option_arg_index]);
        }

        option_arg_index++;
    }

    printf("Application parameters:\n");
    printf("    width=%d\n", width);
    printf("    height=%d\n", height);
    printf("    device=%s\n", device);
    printf("    NATIVE_PLATFORM_NAME=%s\n", NATIVE_PLATFORM_NAME);
#if defined(USE_FB)
    printf("    USE_FB=%d\n", USE_FB);
#elif defined(USE_DRM) && defined(USE_DRM_OPEN)
    printf("    USE_DRM_OPEN=%d\n", 1);
#elif !defined(USE_DRM_OPEN)
    printf("    USE_DRM_OPEN=%d\n", 0);
#endif //USE_FB

    if (Init(&esContext, &userData, "Hello Perfect Square", width, height, device, ES_WINDOW_RGB, DrawPerfectSquare, NULL, NULL, HandleWindowResize, "shaders/basic-color-transform.vs", "shaders/basic.fs"))
    {
        printf("Context initialization failed\n");
        return 1;
    }

    Run(&esContext);

    return 0;
}
