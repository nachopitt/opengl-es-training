#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "gl-utils.h"

const GLfloat PI = 3.14159f;
float elapsedTime = 0.0f;

// The 8x8 monochrome font bitmap for ASCII characters
unsigned char font8x8_basic[128][8] = {
    [ 0] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ASCII 0 (null)
    [ 1] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ASCII 1 (space)
    [65] = {0x18, 0x24, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x00}, // ASCII 65 ('A')
    [66] = {0x7C, 0x42, 0x42, 0x7C, 0x42, 0x42, 0x7C, 0x00}, // ASCII 66 ('B')
    [67] = {0x3C, 0x42, 0x40, 0x40, 0x40, 0x42, 0x3C, 0x00}, // ASCII 67 ('C')
    [68] = {0x7C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7C, 0x00}, // ASCII 68 ('D')
    [69] = {0x7E, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x7E, 0x00}, // ASCII 69 ('E')
    [70] = {0x7E, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x40, 0x00}, // ASCII 70 ('F')
    [71] = {0x3C, 0x42, 0x40, 0x4E, 0x42, 0x42, 0x3C, 0x00}, // ASCII 71 ('G')
    [72] = {0x42, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x00}, // ASCII 72 ('H')
    [73] = {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00}, // ASCII 73 ('I')
    [74] = {0x7E, 0x02, 0x02, 0x02, 0x02, 0x42, 0x3C, 0x00}, // ASCII 74 ('J')
    [75] = {0x42, 0x44, 0x48, 0x70, 0x48, 0x44, 0x42, 0x00}, // ASCII 75 ('K')
    [76] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00}, // ASCII 76 ('L')
    [77] = {0x42, 0x66, 0x5A, 0x5A, 0x42, 0x42, 0x42, 0x00}, // ASCII 77 ('M')
    [78] = {0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x42, 0x00}, // ASCII 78 ('N')
    [79] = {0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00}, // ASCII 79 ('O')
    [80] = {0x7C, 0x42, 0x42, 0x7C, 0x40, 0x40, 0x40, 0x00}, // ASCII 80 ('P')
    [81] = {0x3C, 0x42, 0x42, 0x42, 0x52, 0x4A, 0x3C, 0x00}, // ASCII 81 ('Q')
    [82] = {0x7C, 0x42, 0x42, 0x7C, 0x48, 0x44, 0x42, 0x00}, // ASCII 82 ('R')
    [83] = {0x3C, 0x42, 0x40, 0x3C, 0x02, 0x42, 0x3C, 0x00}, // ASCII 83 ('S')
    [84] = {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}, // ASCII 84 ('T')
    [85] = {0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00}, // ASCII 85 ('U')
    [86] = {0x42, 0x42, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00}, // ASCII 86 ('V')
    [87] = {0x42, 0x42, 0x42, 0x5A, 0x5A, 0x66, 0x42, 0x00}, // ASCII 87 ('W')
    [88] = {0x42, 0x42, 0x24, 0x18, 0x24, 0x42, 0x42, 0x00}, // ASCII 88 ('X')
    [89] = {0x42, 0x42, 0x24, 0x18, 0x18, 0x18, 0x18, 0x00}, // ASCII 89 ('Y')
    [90] = {0x7E, 0x02, 0x04, 0x18, 0x20, 0x40, 0x7E, 0x00}, // ASCII 90 ('Z')
    // More characters can be added as needed...
};

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

// Transform a shape using the vertex shader created in Init()
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

void DrawTextString(ESContext *esContext, char *text, float x, float y, float size) {
    UserData *userData = esContext->userData;

    // Set the viewport
    glViewport(0, 0, esContext->width, esContext->height);

    // Use the program object
    glUseProgram(userData->programObject);

    for (int i = 0; text[i] != '\0'; i++) {
        DrawTextChar(esContext, text[i], x + (i * size * 8), y, size);
    }
}

// Function to draw a single character
void DrawTextChar(ESContext *esContext, char ch, float x, float y, float size) {
    UserData *userData = esContext->userData;

    unsigned char *bitmap = font8x8_basic[(int)ch];

    // Get attribute and uniform locations
    GLint positionAttribute = glGetAttribLocation(userData->programObject, "position");

    // Loop through each row of the 8x8 bitmap
    for (int row = 0; row < 8; row++)
    {
        unsigned char row_data = bitmap[row];

        // Loop through each bit (column) in the row
        for (int col = 0; col < 8; col++)
        {
            if (row_data & (1 << (7 - col)))
            {
                // Set the position for this pixel
                // Adjust positions for NDC (-1 to 1 range)
                float aspect_ratio = esContext->width / esContext->height;
                float x0 = (x + size * (col + 0)) * (aspect_ratio > 1 ? 1.0f / aspect_ratio : 1.0f); // Left
                float x1 = (x + size * (col + 1)) * (aspect_ratio > 1 ? 1.0f / aspect_ratio : 1.0f); // Right
                float y0 = (y - size * (row + 1)) * (aspect_ratio < 1 ? aspect_ratio : 1.0f); // Top
                float y1 = (y - size * (row + 0)) * (aspect_ratio < 1 ? aspect_ratio : 1.0f); // Bottom

                GLfloat quadVertices[] = {
                    x0, y0, // Top left
                    x1, y0, // Top right
                    x0, y1, // Bottom left
                    x1, y1, // Bottom right
                };

                // Bind the vertex data
                glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, quadVertices);
                glEnableVertexAttribArray(positionAttribute);

                // Draw the character quad (two triangles forming a square)
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            }
        }
    }
}

void Run(ESContext* esContext) {
    esMainLoop(esContext);
}

// Get elapsed time in seconds
float GetElapsedTimeInSeconds() {
    return elapsedTime;
}
