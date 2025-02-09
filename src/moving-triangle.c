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

    int width = 1280;
    int height = 480;
    char fb_multi_buffer[12] = "";
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
        else if (strcmp(argv[option_arg_index], "--fb-multi-buffer") == 0) {
            option_arg_index++;
            snprintf(fb_multi_buffer, strlen(argv[option_arg_index]) + 1, "%s", argv[option_arg_index]);
        }

        option_arg_index++;
    }

#ifdef USE_FB
    if (fb_multi_buffer[0] != '\0') {
        long int fb_multi_buffer_number = 1;

        fb_multi_buffer_number = strtol(fb_multi_buffer, NULL, 10);
        if (fb_multi_buffer_number && fb_multi_buffer_number >= 1 && fb_multi_buffer_number <= 3) {
            if (setenv("FB_MULTI_BUFFER", fb_multi_buffer, 1) != 0) {
                fprintf(stderr, "setenv FB_MULTI_BUFFER=%ld error: %s\n", fb_multi_buffer_number, strerror(errno));
            }
            else {
                printf("setenv FB_MULTI_BUFFER=%ld\n", fb_multi_buffer_number);
            }
        }
        else {
            printf("Could not perform string to integer conversion on %s, no setenv call will be performed\n", fb_multi_buffer);
        }
    }
#endif // USE_FB

    printf("Application parameters: \n\tWidth=%d\n\tHeight=%d\n\tDevice=%s\n\tFB_MULTI_BUFFER=%s\n", width, height, device, fb_multi_buffer);

    if (Init(&esContext, &userData, "Hello Triangle", width, height, device, ES_WINDOW_RGB, DrawTriangle, Update, NULL, NULL, "shaders/basic-color-transform.vs", "shaders/basic.fs")) {
        printf("Context initialization failed\n");
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
