#ifndef RENDIX_SHADERS_GLES_SHADER_PROGRAM_H
#define RENDIX_SHADERS_GLES_SHADER_PROGRAM_H

#include <vector>
#include <GLES2/gl2.h>

#include "shaders/IShaderProgram.h"
#include "shaders/GLESShader.h"

namespace rendix::shaders
{
    class GLESShaderProgram : public IShaderProgram
    {
        public:
            GLESShaderProgram();

            unsigned int GetShaderProgramId() const override;
            bool AttachShader(const IShader& shader) override;
            bool LinkShaders() override;
            bool Use() override;
            bool BindAttribute(unsigned int index, const std::string &attribute) override;

        private:
            GLuint shaderProgramId;
    };
}

#endif //RENDIX_SHADERS_GLES_SHADER_PROGRAM_H
