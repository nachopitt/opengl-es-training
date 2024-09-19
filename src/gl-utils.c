#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "gl-utils.h"

const GLfloat PI = 3.14159f;
float elapsedTime = 0.0f;

int Init(ESContext* esContext, UserData* userData, const char* title, GLint width, GLint height, GLuint flags, DrawFunction drawFunction, UpdateFunction updateFunction, char* vShaderFile, char* fShaderFile) {
    esInitContext(esContext);
    esContext->userData = userData;

    esCreateWindow(esContext, title, width, height, flags);

    if (!CompileAndLinkShaders(esContext, vShaderFile, fShaderFile)) {
        return 1;
    }

    esRegisterDrawFunc(esContext, drawFunction);
    esRegisterUpdateFunc(esContext, updateFunction);

    return 0;
}

// Initialize the shader and program object
int CompileAndLinkShaders(ESContext* esContext, char* vShaderFile, char* fShaderFile) {
    UserData* userData = esContext->userData;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = LoadShader(vShaderFile, GL_VERTEX_SHADER);
    fragmentShader = LoadShader(fShaderFile, GL_FRAGMENT_SHADER);

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

    return TRUE;
}

// Create a shader object, load the shader source, and compile the shader
GLuint LoadShader(const char* fileName, GLenum type) {
    GLuint shader;
    GLint compiled;
    FILE *fileHandle;
    long fileSize;

    // Create the shader object
    shader = glCreateShader(type);

    if (shader == 0)
        return 0;

    fileHandle = fopen(fileName, "r");
    if (fileHandle == NULL)
    {
        perror(fileName);

        return 0;
    }

    fseek(fileHandle, 0, SEEK_END);
    fileSize = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET); /* same as rewind(f); */

    GLchar *sourceCode = malloc(fileSize + 1);
    memset(sourceCode, 0, fileSize + 1);
    fread(sourceCode, 1, fileSize, fileHandle);
    fclose(fileHandle);

    // Load the shader source
    glShaderSource(shader, 1, (const GLchar* const *)&sourceCode, NULL);

    free(sourceCode);

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

// Clear the screen with some color
void ClearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    // Clear the screen with some color
    glClearColor(red, green, blue, alpha);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);
}

// Draw a shape using the shader pair created in Init()
void DrawShape(ESContext* esContext, GLenum primitivesType, GLfloat vVertices[], GLint vertexComponentSize, GLenum vertexComponentType, GLfloat vColors[], GLint colorComponentSize, GLenum colorComponentType, GLint indicesCount) {
    UserData* userData = esContext->userData;

    ClearScreen(0.0f, 0.0f, 0.0f, 1.0f);

    // Set the viewport
    glViewport(0, 0, esContext->width, esContext->height);

    // Use the program object
    glUseProgram(userData->programObject);

    // Load the vertex data
    glVertexAttribPointer(0, vertexComponentSize, vertexComponentType, GL_FALSE, 0, vVertices);
    glVertexAttribPointer(1, colorComponentSize, colorComponentType, GL_FALSE, 0, vColors);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(primitivesType, 0, indicesCount);
}

//Transform a shape using the fragment shader created in Init()
void TransformShape(ESContext* esContext, GLfloat angle, GLfloat x_distance, char* modelViewProjectionUniform) {
    UserData* userData = esContext->userData;

    // Calculate model-view-projection matrix
    float radians = angle * PI / 180.0f;
    float cosTheta = cos(radians);
    float sinTheta = sin(radians);
    float aspect = esContext->width / esContext->height;

    float modelViewProjection[] = {
        cosTheta,   -sinTheta * aspect, 0.0f, 0.0f,
        sinTheta,   cosTheta * aspect,  0.0f, 0.0f,
        0.0f,       0.0f,               1.0f, 0.0f,
        x_distance, 0.0f,               0.0f, 1.0f
    };

    // Get the location of the modelViewProjection uniform
    GLint mvpLoc = glGetUniformLocation(userData->programObject, modelViewProjectionUniform);

    // Pass the rotation matrix to the shader
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, modelViewProjection);
}

void Run(ESContext* esContext) {
    esMainLoop(esContext);
}

// Get elapsed time in seconds
float GetElapsedTimeInSeconds() {
    return elapsedTime;
}
