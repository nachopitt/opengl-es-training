#ifndef GL_UTILS
#define GL_UTILS

#include "esUtil.h"

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

// Draw a shape using the shader pair created in Init()
void DrawShape(ESContext* esContext, GLenum primitivesType, GLfloat vVertices[], GLint vertexComponentSize, GLenum vertexComponentType, GLfloat vColors[], GLint colorComponentSize, GLenum colorComponentType, GLint indicesCount);

//Rotate a shape using the fragment shader created in Init()
void RotateShape(ESContext* esContext, GLfloat angle, char* modelViewProjectionUniform);

// Start main loop
void Run(ESContext* esContext);

#endif // GL_UTILS
