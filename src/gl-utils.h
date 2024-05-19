#ifndef GL_UTILS
#define GL_UTILS

#include "esUtil.h"

typedef struct {
    // Handle to a program object
    GLuint programObject;
} UserData;

// Create a shader object, load the shader source, and compile the shader
GLuint LoadShader(const GLchar* shaderSrc, GLenum type);

// Initialize the shader and program object
int CompileAndLinkShaders(ESContext* esContext);

// Draw a shape using the shader pair created in Init()
void DrawShape(ESContext* esContext, GLenum primitivesType, GLfloat vVertices[], GLint vertexComponentSize, GLenum vertexComponentType, GLfloat vColors[], GLint colorComponentSize, GLenum colorComponentType, GLint indicesCount);

#endif // GL_UTILS
