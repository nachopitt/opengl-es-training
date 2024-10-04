#ifndef RENDIX_SHADERS_SHADER_PROGRAM_H
#define RENDIX_SHADERS_SHADER_PROGRAM_H

#include <vector>
#include <GLES2/gl2.h>

#include "shaders/Shader.h"

namespace rendix::shaders
{
    class ShaderProgram
    {
        public:
            ShaderProgram();
            GLuint GetShaderProgramId() const;
            bool AttachShader(const Shader& shader);
            bool LinkShaders();
            bool BindAttribute(GLuint index, const GLchar* attribute);

        private:
            GLuint shaderProgramId;
    };
}

#endif //RENDIX_SHADERS_SHADER_PROGRAM_H
