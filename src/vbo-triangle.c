#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "esUtil.h"
#include "gl-utils.h"

typedef struct {
    UserData userData;
    GLuint vboIds[2];
} CustomUserData;

void onWindowResize(ESContext *esContext, int width, int height)
{
    printf("window has resized to %dx%d\n", width, height);

    esContext->width = width;
    esContext->height = height;
}

// Draw a triangle using the shader pair created in Init()
void onDraw(ESContext *esContext)
{
    CustomUserData* userData = esContext->userData;

    // Call gl-utils's SetViewport function
    SetViewport(esContext);

    // Call gl-utils's ClearScreen function
    ClearScreen(0.0f, 0.0f, 0.0f, 1.0f);

    // Use the program object
    glUseProgram(userData->userData.programObject);

    // Load the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[1]);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    // glBindAttribLocation(userData->userData.programObject, 0, "vPosition");
    // glBindAttribLocation(userData->userData.programObject, 1, "aColor");

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, char *argv[])
{
    ESContext esContext;
    CustomUserData userData;

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

    printf("Application parameters: \n\tWidth=%d\n\tHeight=%d\n\tDevice=%s\n", width, height, device);

    if (Init(&esContext, (UserData*)&userData, "Hello World VBO Triangle!", width, height, device, ES_WINDOW_RGB, onDraw, NULL, NULL, onWindowResize, "shaders/basic-color.vs", "shaders/basic.fs"))
    {
        perror("Init context");
        return 1;
    }

    // vboIds[0] – used to store vertex position attribute data
    // vboIds[1] – used to store vertex color attribute data
    glGenBuffers(2, userData.vboIds);

    glBindBuffer(GL_ARRAY_BUFFER, userData.vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, userData.vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vColors), vColors, GL_STATIC_DRAW);

    Run(&esContext);

    glDeleteBuffers(2, userData.vboIds);

    return 0;
}
