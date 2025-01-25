#ifndef GL_UTILS
#define GL_UTILS

#include "esUtil.h"

#define SHADER_TYPE_STR(type) (type == GL_VERTEX_SHADER ? "GL_VERTEX_SHADER" : (type == GL_FRAGMENT_SHADER ? "GL_FRAGMENT_SHADER" : "UNKNOWN"))

extern const GLfloat PI;
extern float elapsedTime;

typedef struct {
    // Handle to a program object
    GLuint programObject;
} UserData;

typedef struct {
    // Handle to a shader object
    GLuint shaderObject;
    char* shaderFileName;
    char* shaderSourceCode;
} Shader;

typedef void (ESCALLBACK *DrawFunction)(ESContext*);
typedef void (ESCALLBACK *UpdateFunction)(ESContext *, float);
typedef void (ESCALLBACK *KeyFunction)(ESContext *, unsigned char, int, int);
typedef void (ESCALLBACK *WindowResizeFunction)(ESContext *, int, int);

// Initialize context, window, shaders and callback functions
int Init(ESContext* esContext, UserData* userData, const char* title, GLint width, GLint height, GLuint flags, DrawFunction drawFunction, UpdateFunction updateFunction, KeyFunction keyFunction, WindowResizeFunction windowResizeFunction, char* vShaderFile, char* fShaderFile);

// Set the viewport in case it has changed
void SetViewport(ESContext* esContext);

// Initialize the shader and program object
int CompileAndLinkShaders(ESContext* esContext, char* vShaderFile, char* fShaderFile);

// Create a shader object, load the shader source, and compile the shader
GLuint LoadShader(const char* fileName, GLenum type);

// Clear the screen with some color
void ClearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

// Draw a shape using the shader pair created in Init()
void DrawShape(ESContext* esContext, GLenum primitivesType, GLfloat vVertices[], GLint vertexComponentSize, GLenum vertexComponentType, GLfloat vColors[], GLint colorComponentSize, GLenum colorComponentType, GLint indicesCount);

// Project a shape using the vertex shader created in Init()
void ProjectShape(ESContext* esContext, char* modelViewProjectionUniform);

// Transform a shape using the vertex shader created in Init()
void TransformShape(ESContext* esContext, GLfloat angle, GLfloat x_distance, char* modelViewProjectionUniform);

// Draw a text string using the shader pair created in Init()
void DrawTextString(ESContext *esContext, char *text, float x, float y, float size);

// Draw a text character using the shader pair created in Init()
void DrawTextChar(ESContext *esContext, char ch, float x, float y, float size);

// Start main loop
void Run(ESContext* esContext);

// Get elapsed time in seconds
float GetElapsedTimeInSeconds();

#endif // GL_UTILS
