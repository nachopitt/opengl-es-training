#ifndef GL_UTILS
#define GL_UTILS

#include "esUtil.h"

extern const GLfloat PI;

typedef struct {
    // Handle to a program object
    GLuint programObject;
} UserData;

typedef void (ESCALLBACK *DrawFunction)(ESContext*);

// Initialize context, window, shaders and drawing function
int Init(ESContext* esContext, UserData* userData, const char* title, GLint width, GLint height, GLuint flags, DrawFunction drawFunction, char* vShaderFile, char* fShaderFile);

// Initialize the shader and program object
int CompileAndLinkShaders(ESContext* esContext, char* vShaderFile, char* fShaderFile);

// Create a shader object, load the shader source, and compile the shader
GLuint LoadShader(const GLchar* shaderSrc, GLenum type);

// Clear the screen with some color
void ClearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

// Draw a shape using the shader pair created in Init()
void DrawShape(ESContext* esContext, GLenum primitivesType, GLfloat vVertices[], GLint vertexComponentSize, GLenum vertexComponentType, GLfloat vColors[], GLint colorComponentSize, GLenum colorComponentType, GLint indicesCount);

//Transform a shape using the fragment shader created in Init()
void TransformShape(ESContext* esContext, GLfloat angle, GLfloat x_distance, char* modelViewProjectionUniform);

// Start main loop
void Run(ESContext* esContext);

// Get the current time in seconds
float GetCurrentTimeInSeconds();

#endif // GL_UTILS
