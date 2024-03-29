#include <stdlib.h>
#include <stdio.h>

#include "gl-utils.h"

// Create a shader object, load the shader source, and compile the shader
GLuint LoadShader(const GLchar* shaderSrc, GLenum type) {
    GLuint shader;
    GLint compiled;

    // Create the shader object
    shader = glCreateShader(type);

    if (shader == 0)
        return 0;

    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        GLint infoLen = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            char* infoLog = malloc(sizeof(char) * infoLen);

            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            esLogMessage("Error compiling shader:\n%s\n", infoLog);

            free(infoLog);
        }

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

// Initialize the shader and program object
int Init(ESContext* esContext) {
    UserData* userData = esContext->userData;
    GLchar vShaderStr[] =
        "attribute vec4 vPosition;\n"
        "attribute vec4 aColor;\n"
        "varying vec4 vColor;\n"
        "void main()\n"
        "{\n"
        "   vColor = aColor;\n"
        "   gl_Position = vPosition;\n"
        "}\n";

    GLchar fShaderStr[] =
        "precision mediump float;\n"
        "varying vec4 vColor;\n"
        "void main()\n"
        "{\n"
        "   gl_FragColor = vColor;\n"
        "}\n";

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = LoadShader(vShaderStr, GL_VERTEX_SHADER);
    fragmentShader = LoadShader(fShaderStr, GL_FRAGMENT_SHADER);

    // Crete the program object
    programObject = glCreateProgram();

    if (programObject == 0)
        return 0;

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    // Bind vPosition to attribute 0
    glBindAttribLocation(programObject, 0, "vPosition");

    // Link the program
    glLinkProgram(programObject);

    // Check the link status
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

    if (!linked) {
        GLint infoLen = 0;

        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            char* infoLog = malloc(sizeof(char) * infoLen);

            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            esLogMessage("Error linking program:\n%s\n", infoLog);

            free(infoLog);
        }

        glDeleteProgram(programObject);
        return FALSE;
    }

    // Store the program object
    userData->programObject = programObject;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return TRUE;
}

// Draw a shape using the shader pair created in Init()
void DrawShape(ESContext* esContext, GLenum primitivesType, GLfloat vVertices[], GLint vertexComponentSize, GLenum vertexComponentType, GLfloat vColors[], GLint colorComponentSize, GLenum colorComponentType, GLint indicesCount) {
    UserData* userData = esContext->userData;

    // Set the viewport
    glViewport(0, 0, esContext->width, esContext->height);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the program object
    glUseProgram(userData->programObject);

    // Load the vertex data
    glVertexAttribPointer(0, vertexComponentSize, vertexComponentType, GL_FALSE, 0, vVertices);
    glVertexAttribPointer(1, colorComponentSize, colorComponentType, GL_FALSE, 0, vColors);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(primitivesType, 0, indicesCount);

    eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

