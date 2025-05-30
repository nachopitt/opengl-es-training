#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "esUtil.h"
#include "gl-utils.h"

// Get the elapsed time as a delta
void Update(ESContext* esContext, float deltaTime) {
    elapsedTime += deltaTime;
}

// Draw a triangle using the shader pair created in Init()
void DrawTriangle(ESContext* esContext) {
    // Rotation angle
    static GLfloat angle = 0.0f;
    GLfloat x_distance = 0.0f;
    float speed_factor = 2.0f;
    // Get elapsed time in seconds
    float time = GetElapsedTimeInSeconds();

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

    SetViewport(esContext);

    // Call gl-utils's ClearScreen function
    ClearScreen(0.0f, 0.0f, 0.0f, 1.0f);

    // Call gl-utils's TransformShape function
    TransformShape(esContext, 0, x_distance, "modelViewProjection");

    // Call gl-utils's DrawShape function
    DrawShape(esContext, GL_TRIANGLES, vVertices, 3, GL_FLOAT, vColors, 4, GL_FLOAT, 3);
}

int main(int argc, char* argv[]) {
    ESContext esContext;
    UserData userData;

    int argc_window_size_offset = 0;
#ifdef USE_FB
    argc_window_size_offset = 1;

    if (argc > 1) {
        long int fb_multi_buffer = 1;

        fb_multi_buffer = strtol(argv[1], NULL, 10);
        if (fb_multi_buffer && fb_multi_buffer >= 1 && fb_multi_buffer <= 3) {
            if (setenv("FB_MULTI_BUFFER", argv[1], 1) != 0) {
                fprintf(stderr, "setenv FB_MULTI_BUFFER=%ld error: %s\n", fb_multi_buffer, strerror(errno));
            }
            else {
                printf("setenv FB_MULTI_BUFFER=%ld\n", fb_multi_buffer);
            }
        }
        else {
            printf("Could not perform string to integer conversion on %s, no setenv call will be performed\n", argv[1]);
        }
    }
#endif // USE_FB

    int width = 1280;
    int height = 480;

    if (argc > argc_window_size_offset + 1) {
        width = atoi(argv[argc_window_size_offset + 1]);
    }

    if (argc > argc_window_size_offset + 2) {
        height = atoi(argv[2]);
    }

    if (Init(&esContext, &userData, "Hello Triangle", width, height, ES_WINDOW_RGB, DrawTriangle, Update, NULL, NULL)) {
        printf("Context initialization failed\n");
        return 1;
    }

    if (!CompileAndLinkShaders(&esContext, "shaders/basic-color-transform.vs", "shaders/basic.fs")) {
        return 1;
    }

#ifdef USE_FB
    char* fb_multi_buffer_env_var_value = getenv("FB_MULTI_BUFFER");

    if (fb_multi_buffer_env_var_value != NULL) {
        printf("getenv FB_MULTI_BUFFER=%s\n", fb_multi_buffer_env_var_value);
    }
    else {
        printf("getenv FB_MULTI_BUFFER doesn't exist!\n");
    }
#endif //USE_FB

    Run(&esContext);

    return 0;
}
